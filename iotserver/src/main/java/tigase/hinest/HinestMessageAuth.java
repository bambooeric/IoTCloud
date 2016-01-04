package tigase.hinest;

import static tigase.db.RepositoryFactory.GEN_USER_DB_URI_PROP_KEY;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayDeque;
import java.util.Date;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Properties;
import java.util.Queue;
import java.util.UUID;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;

import com.cloopen.rest.sdk.utils.encoder.BASE64Encoder;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import java.security.InvalidKeyException;  
import java.security.NoSuchAlgorithmException;  
  
import javax.crypto.Mac;  
import javax.crypto.spec.SecretKeySpec;  

import tigase.conf.ConfiguratorAbstract;
import tigase.db.AuthRepository;
import tigase.db.DBInitException;
import tigase.db.DataRepository;
import tigase.db.NonAuthUserRepository;
import tigase.db.RepositoryFactory;
import tigase.db.TigaseDBException;
import tigase.db.UserRepository;
import tigase.form.Field;
import tigase.form.Form;
import tigase.form.FormSignatureVerifier;
import tigase.form.FormSignerException;
import tigase.form.SignatureCalculator;
import tigase.hinest.db.AuthManagerRepository;
import tigase.hinest.db.AuthManagerRepositoryMDImpl;
import tigase.hinest.db.TurnRepository;
import tigase.hinest.db.TurnRepositoryMDImpl;
import tigase.server.Command;
import tigase.server.Iq;
import tigase.server.Message;
import tigase.server.Packet;
import tigase.server.Priority;
import tigase.util.ElementUtils;
import tigase.util.TigaseStringprepException;
import tigase.xml.Element;
import tigase.xml.XMLUtils;
import tigase.xmpp.Authorization;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;
import tigase.xmpp.NoConnectionIdException;
import tigase.xmpp.NotAuthorizedException;
import tigase.xmpp.PacketErrorTypeException;
import tigase.xmpp.StanzaType;
import tigase.xmpp.XMPPException;
import tigase.xmpp.XMPPPacketFilterIfc;
import tigase.xmpp.XMPPProcessor;
import tigase.xmpp.XMPPProcessorIfc;
import tigase.xmpp.XMPPResourceConnection; 

public class HinestMessageAuth extends XMPPProcessor implements XMPPPacketFilterIfc { 
	/* load id name */
    private static final String XMLNS = "hinest:xmpp:messageauth";
    /* Define the plugin ID */  
    private static final String ID = XMLNS;  
	
	/* Log output */
	private static Logger log = Logger.getLogger(HinestExtdiscoICE.class.getName());
	private static final String SUBJECT = "subject";
	private static final String BODY = "body";	
	private static final String HISNET = "hisnet";
	private static final String[] MESSAGE = { Message.ELEM_NAME };
	private static final String[] IQ_HISNET = { Iq.ELEM_NAME, HISNET};
	private static final String[] MESSAGE_SUBJECT = { Message.ELEM_NAME, SUBJECT };
	private static final String[] MESSAGE_BODY = { Message.ELEM_NAME, BODY };
	
    /* xmlname and elements */
	private static final String HISNET_XMLNS = "hinest:iq:hisnet";
	private static final String[] XMLNSS = { Message.CLIENT_XMLNS, HISNET_XMLNS};
    private static final String[][] ELEMENTS = { MESSAGE, IQ_HISNET};
    
	private static String DEV_DOMAIN = "dev.hinest";
	private static String USR_DOMAIN = "usr.hinest";
	
	@Override
	public String id() {
		// TODO Auto-generated method stub
		return ID;
	}
    
	/**
	 * Helper method removing packets from processing queue and generating
	 * appropriate error packet to be send back to client
	 *
	 * @param it iterator over collection of packets being filtered
	 * @param res currently processed packet
	 * @param errors collection of outgoing errors
	 * @param msg human readable error message
	 */
	private void removePacket(Iterator<Packet> it, Packet res, Queue<Packet> errors, String msg) {
		if (it != null) {
			it.remove();
		}
		try {
			errors.add(Authorization.FORBIDDEN.getResponseMessage(res, msg, true));
		} catch (PacketErrorTypeException ex) {
			log.log(Level.FINE, "Already error packet, dropping it..: {0}", res);
		}
	}
	
	private void filterIqHisnet(Packet res, Iterator<Packet> it, Queue<Packet> errors, 
						XMPPResourceConnection session) throws NotAuthorizedException {
		
	}
	
	private void filterMessge(Packet res, Iterator<Packet> it, Queue<Packet> errors, 
						XMPPResourceConnection session) throws NotAuthorizedException {
		if (!(res.getType() != StanzaType.error) && ((((res.getStanzaFrom() != null) &&
				!session.isUserId(res.getStanzaFrom().getBareJID())) || ((res
				.getStanzaTo() != null) &&!session.isUserId(res.getStanzaTo()
				.getBareJID()))))) {	
			return;
		}

		// TODO BareJID
		BareJID user_id = null;
		BareJID to_user = null;
		if (res.getStanzaFrom() != null) {
			user_id = res.getStanzaFrom().getBareJID();
		} else {
			return;
		}		
		
		if (res.getStanzaTo() != null) {
			to_user = res.getStanzaTo().getBareJID();
		} else {
			return;
		}
		
		//只对终端用户访问进行权限控制
		if ((res.getPacketFrom() != null) &&
			session.isAuthorized() && 
			user_id.getDomain().equals(USR_DOMAIN)) {
			
			//获取body对象中json的值
			Element request = res.getElement();
			Element services = request.findChild(MESSAGE_BODY);
			if (null == services) {
				removePacket(it, res, errors, "no authority operate, message blocked.");
				return;
			}
			
			//判断业务类别    
			byte auth_sub_class = -1;
			long auth_val = -1;
			
			String json = services.getCData();
			
			//对关键消息进行控制，非关键消息直接转发
			if (json.charAt(0) != '{' || json.charAt(json.length() - 1) != '}') {
				//数据转发
				return;
			}
			
			//json 转意
			json = json.replace("&quot;", "\"");
			
			System.out.println(json);
			
			JSONObject object=JSONObject.fromObject(json);
			if (null != object.get("cmd")) {
				String cmd = "" + object.get("cmd");
				switch (cmd) {
				case "standby":
				case "reboot":
				case "osdtime":
				case "osdtitle":
				case "alarm":	
				case "timezone":
				case "light":
				case "videostandard":
				case "mirror":
				case "flip":
				case "getprop":
					auth_sub_class = AuthManagerRepository.AUTH_SUB_CLASS_CONTROL;
					auth_val = AuthManagerRepository.AUTH_ATTR_VAL_DEFUALT;
					
					break;
				default:
					break;
				}
			} else if (null != object.get("eventName")) {
				String cmd = "" + object.get("eventName");
				switch (cmd) {
				case "offer":
					auth_sub_class = AuthManagerRepository.AUTH_SUB_CLASS_ORDER;
					auth_val = AuthManagerRepository.AUTH_ATTR_VAL_DEFUALT;
				default:
					break;
				}
			} else {
				return;
			}
			
			//是否有权限
			boolean ret = false;
			if (-1 != auth_sub_class && -1 != auth_val) {
				AuthManagerRepository auth_m_repo = new AuthManagerRepositoryMDImpl();
				ret = auth_m_repo.findAuthRouteIs(user_id, to_user.toString(), 
													 auth_sub_class, auth_val);
			}
			
			//消息处理
			if (true == ret) {
				//允许通过
				return;
			} else {
				//不允许通过
				removePacket(it, res, errors, "Communication blocked.");
				
				return;
			}
		}
	}
	
	@Override
	public void filter(Packet packet, XMPPResourceConnection session, NonAuthUserRepository repo,
			Queue<Packet> results) {
		// TODO Auto-generated method stub
		if (log.isLoggable(Level.FINEST)) {
			log.finest("Processing packet: " + packet.toString());
		}

		if ((session == null) || (results == null) || (results.size() == 0)) {
			return;
		}
		
		if (session == null || session.getAuthState() != Authorization.AUTHORIZED) {
			if (log.isLoggable(Level.FINEST)) {
				log.finest("Session is null, ignoring");
			}

			return;
		} // end of if (session == null)
		
		Queue<Packet> errors = new ArrayDeque<Packet>(1);
		
		try {
			for (Iterator<Packet> it = results.iterator(); it.hasNext(); ) {
				Packet res = it.next();
				
				if ( log.isLoggable( Level.FINEST ) ){
					log.log( Level.FINEST, "Filtering (result): {0}", res );
				}
				
				//策略:对重点关键的消息进行消息过滤，其他消息直接放行。
				if (res.isXMLNSStaticStr(MESSAGE, Message.CLIENT_XMLNS)) {
					//过滤message消息
					filterMessge(res, it, errors, session);
					
					continue;
				} else if (res.isXMLNSStaticStr(IQ_HISNET, HISNET_XMLNS)) {
					//过滤hisnet消息
					filterIqHisnet(res, it, errors, session);
					
					continue;
				} else {
					//直接放行
					continue;
				}
			}
		} catch (NotAuthorizedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@Override
	public String[][] supElementNamePaths() {
		return ELEMENTS;
	}

	@Override
	public String[] supNamespaces() {
		return XMLNSS;
	}
}


