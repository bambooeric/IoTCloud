package tigase.hinest;

import static tigase.db.RepositoryFactory.GEN_USER_DB_URI_PROP_KEY;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;
import java.util.Enumeration;
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
import tigase.hinest.db.TurnRepository;
import tigase.hinest.db.TurnRepositoryMDImpl;
import tigase.server.Command;
import tigase.server.Iq;
import tigase.server.Packet;
import tigase.server.Priority;
import tigase.util.ElementUtils;
import tigase.util.TigaseStringprepException;
import tigase.xml.Element;
import tigase.xml.XMLUtils;
import tigase.xmpp.Authorization;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;
import tigase.xmpp.NotAuthorizedException;
import tigase.xmpp.StanzaType;
import tigase.xmpp.XMPPException;
import tigase.xmpp.XMPPProcessor;
import tigase.xmpp.XMPPProcessorIfc;
import tigase.xmpp.XMPPResourceConnection; 


/** 
 * received message
 * <iq from='usr_ttt@192.168.1.107' id='yv2c19f7' to='192.168.1.107' type='get'>
 *     <services xmlns='urn:xmpp:extdisco:1'/>
 * </iq>
 * 
 * send message 
 * <iq from='shakespeare.lit' id='yv2c19f7' to='bard@shakespeare.lit/globe' type='result'>
 *     <services xmlns='urn:xmpp:extdisco:1'>
 *     		<service host='stun.shakespeare.lit'
 *     				 port='998'
 *                   transport='udp'
 *                   type='stun'/>
 *     		<service host='relay.shakespeare.lit'
 *     				 port='998'
 *                   transport='udp'
 *                   type='turn'
 *                   username='nb789321kjlskjfdb7g8'
 *                   password='jj9999929jkj5sadjfj93v3n'/>  
 *     <services/>       
 **/
public class HinestExtdiscoICE extends XMPPProcessor implements XMPPProcessorIfc { 
	/* load id name */
    private static final String XMLNS = "hinest:xmpp:extdisco_ice";
    /* Define the plugin ID */  
    private static final String ID = XMLNS;  
	
	/* Log output */
	private static Logger log = Logger.getLogger(HinestExtdiscoICE.class.getName());
	private static final String SERVICES = "services";
	private static final String SERVICE = "service";
	private static final String[] IQ_SERVICES = { Iq.ELEM_NAME, SERVICES };
	private static final String[] IQ_SERVICES_CHILD = { Iq.ELEM_NAME, SERVICES, SERVICE };
	
    /* xmlname and elements */
	private static final String[] XMLNSS = { "urn:xmpp:extdisco:1" };
    private static final String[][] ELEMENTS = { IQ_SERVICES };
    
    /* turn repository */
    private static TurnRepository turn_repo = null;

    /* username and password random */
    private static final int USERNAME_RANDOM_LENGTH = 16;
    private static final int PASSWORD_RANDOM_LENGTH = 16;
	private static final int SHATYPE_SHA256 = 1;   
	private static final int SHATYPE_MD5 = 2;
	
	private static final int TURN_MODE_REST_API = 1;
	private static final int TURN_MODE_COMMON = 2;
	
	private static final int TURN_REST_API_TIME_OUT_SECOND = 86400;
    
	private static final String HMAC_SHA1 = "HmacSHA1"; 
	
	@Override
	public String id() {
		// TODO Auto-generated method stub
		return ID;
	}
	
	private void storeTurnUser(BareJID user_id, String user_name, String hmac_key) {
		if (null == turn_repo) {
			turn_repo = new TurnRepositoryMDImpl();
		}
		
		try {
			turn_repo.addTurnUser(user_id, user_name, hmac_key);
		} catch (TigaseDBException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private String getSharedSecret(BareJID user_id) {
		String secret = null;
		if (null == turn_repo) {
			turn_repo = new TurnRepositoryMDImpl();
		}
		
		secret = turn_repo.getShareSecret(user_id);
		
		return secret;
	}
	
	
	private static String hexToString(byte[] b) { 
		String str = "";
		
		for (int i = 0; i < b.length; i++) { 
			String hex = Integer.toHexString(b[i] & 0xFF); 
			if (1 == hex.length()) {
				hex = '0' + hex;
			}
			str = str + hex;
		} 
			
		return str;
	} 

	private static byte[] stringToHex(String b) { 
		byte[] hex = new byte[b.length()];

		for (int i = 0; i < b.length(); i++) {
			hex[i] = (byte)(b.charAt(i) & 0xFF); 
		} 
			
		return hex;
	} 
	
	public static final String randomString(int length) {
		char[] numbersAndLetters = null;
		
        if (length < 1) {
            return null;
        }
        
        numbersAndLetters = ("0123456789abcdefghijklmnopqrstuvwxyz" +
                	   "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ").toCharArray();
        
		SecureRandom random = null;
		char[] randBuffer = null;
		
		try {
			//SecureRandom.getInstanceStrong()
			random = SecureRandom.getInstance("SHA1PRNG");
	        randBuffer = new char[length];
	        
	        for (int i=0; i<randBuffer.length; i++) {
	            randBuffer[i] = numbersAndLetters[random.nextInt(numbersAndLetters.length)];
	        }
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
      
        return new String(randBuffer);
	}
	
	private void productTurnUserPasswd(BareJID user, String[] user_name, String[] password, int mode)  {
		java.security.Security.addProvider(new com.sun.crypto.provider.SunJCE()); 
		if (TURN_MODE_REST_API == mode) {
			Date date = new Date();
			long time = date.getTime() / 1000 +  TURN_REST_API_TIME_OUT_SECOND;
			String random_user = randomString(USERNAME_RANDOM_LENGTH);
			user_name[0] = time + ":" + random_user;
			
			String secret = getSharedSecret(user);
			if (null != secret) {
				/* **********************************************************
				 * calc password
				 * usercombo -> "timestamp:userid"
				 * turn user -> usercombo
				 * turn password -> base64(hmac(secret key, usercombo))
				 ************************************************************/
		        SecretKeySpec secretKey = new SecretKeySpec(stringToHex(secret), HMAC_SHA1);  
		        Mac mac;
				try {
					mac = Mac.getInstance(secretKey.getAlgorithm());
			        mac.init(secretKey); 
			        byte[] rawHmac = mac.doFinal(stringToHex(user_name[0])); 
			        
			        password[0] = Base64.encodeBase64String(rawHmac);
			        
			        System.out.println("password hmac:" + hexToString(rawHmac) + " base64:" + password[0]);
			        
			        //password[0] = base64_encode(rawHmac);
				} catch (NoSuchAlgorithmException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InvalidKeyException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}  
			} else {
				log.info("rest api mode turn share secret no exist!");
			}
		} else if (TURN_MODE_COMMON == mode) {
			user_name[0] = randomString(USERNAME_RANDOM_LENGTH);
			password[0] = randomString(PASSWORD_RANDOM_LENGTH);
		}
		//user_name[0] = "test";
		//password[0] = "123456";
		
//		try {
//			random = SecureRandom.getInstance("SHA1PRNG");
//			
//			/* product user name ramdom */
//			byte user_bytes[] = new byte[USERNAME_RANDOM_LENGTH];
//			random.nextBytes(user_bytes);
//			SASLprep(user_bytes);
//			user_name[0] = hexToString(user_bytes);
//			
//			System.out.println("random user name :" + user_name[0]);
//			
//			/* product password ramdom */
//			byte passwd_bytes[] = new byte[PASSWORD_RANDOM_LENGTH];
//			random.nextBytes(passwd_bytes);
//			SASLprep(passwd_bytes);
//			password[0] = hexToString(passwd_bytes);
//			
//			System.out.println("random password :" + password[0]);			
//		} catch (NoSuchAlgorithmException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} 
	}
	
	private int SASLprep(byte[] s)
	{
		if(null != s) {
			byte[] strin = s;
			byte[] strout = s;
			int idx_in = 0;
			int idx_out = 0;
			for(;;) {
				if(s.length == idx_out) {
					break;
				}

				byte c = strin[idx_in];
				switch(c) {
				case (byte) 0xAD:
					++idx_in;
					break;
				case (byte) 0xA0:
				case 0x20:
					strout[idx_out] = 0x20;
					++idx_out;
					++idx_in;
					break;
				case 0x7F:
					return -1;
				default:
					if(c<0x1F)
						return -1;
					if(c>=0x80 && c<=0x9F)
						return -1;
					strout[idx_out] = c;
					++idx_out;
					++idx_in;
				}
			}
		}

		return 0;
	}
	
	private byte[] productHmacKey(byte[] uname, byte[] realm, byte[] upwd, int shatype)
	{
		int ulen = uname.length;
		int rlen = realm.length;
		int plen = upwd.length;
		int strl = ulen+1+rlen+1+plen;
		byte[] str = new byte[strl];
		byte[] str_key;
		MessageDigest sha = null;
		
		if (0 != SASLprep(upwd)) {
			log.info("Password SASLprep error!");
		}

		System.arraycopy(uname, 0, str, 0, ulen);
		str[ulen]=':';
		System.arraycopy(realm, 0, str, ulen+1, rlen);
		str[ulen+1+rlen]=':';
		System.arraycopy(upwd, 0, str, ulen+1+rlen+1, plen);

		if(shatype == SHATYPE_SHA256) {
			try {
				sha = MessageDigest.getInstance("SHA-256");
			} catch (NoSuchAlgorithmException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else {
			try {
				sha= MessageDigest.getInstance("MD5");
			} catch (NoSuchAlgorithmException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		sha.update(str);
		str_key = sha.digest();
		
		return str_key;
	}
	
	private final static String GEN_STUN_URI_PROP_KEY = "stun-uri";
	private final static String GEN_TURN_URI_PROP_KEY = "turn-uri";

	private int getStunProperty(String uri, String[] host, String[] port, String[] transport) {
		String[] param_url = null;
		String[] host_port = null;
		String[] parameters = null;
		String[] parameter = null;
		
		/* split host_port and other parameters */
		param_url = uri.split(",");
		if (null == param_url || param_url.length < 2) {
			log.info("parse stun url error, param_url:" + param_url.length + "," + param_url[0].toString());
			return -1;
		}
		
		/* parse host and port */
		host_port = param_url[0].split(":");
		if (null == host_port || host_port.length < 2) {
			log.info("parse stun url host port error!");
			return -1;
		}
		host[0] = host_port[0];
		port[0] = host_port[1];
		
		/* parse other parameters */
		parameters = param_url[1].split("&");
		for (int i = 0; i < parameters.length; i++) {
			parameter = parameters[i].split("=");
			if (null == parameter || parameter.length < 1) {
				log.info("parse stun url parameter error!");
			}
			if (parameter[0].equals("transport")) {
				transport[0] = parameter[1];
			}
		}
		
		return 0;
	}
	
	private int getTurnProperty(String url, String[] host, String[] port, 
						    String[] transport, String[] realm, int[] mode) {
		String[] param_url = null;
		String[] host_port = null;
		String[] parameters = null;
		String[] parameter = null;

		/* split host_port and other parameters */
		param_url = url.split(",");
		if (null == param_url || param_url.length < 2) {
			log.info("parse trun url error!");
			return -1;
		}
		
		/* parse host and port */
		host_port = param_url[0].split(":");
		if (null == host_port || host_port.length < 2) {
			log.info("parse trun url host port error!");
			return -1;
		}
		host[0] = host_port[0];
		port[0] = host_port[1];
		
		/* parse other parameters */
		parameters = param_url[1].split("&");
		for (int i = 0; i < parameters.length; i++) {
			parameter = parameters[i].split("=");
			if (null == parameter || parameter.length < 2) {
				log.info("parse trun url parameter error!");
			}
			if (parameter[0].equals("transport")) {
				transport[0] = parameter[1];
			} else if (parameter[0].equals("realm")) {
				realm[0] = parameter[1];
			} else if (parameter[0].equals("mode")) {
				if (parameter[1].equals("rest_api")) {
					mode[0] = TURN_MODE_REST_API;
				} else {
					mode[0] = TURN_MODE_COMMON;
				}
			}
		}
		
		return 0;
	}
	
	private Packet respProcess(BareJID user_id, XMPPResourceConnection session, Packet packet) {
		Packet pack_res = null;
		
		/* product turn user_name and password */
		String[] user_name = new String[1];
		String[] password = new String[1];
		String[] hmac_key = new String[1];

		String[] host_name = new String[1];
		String[] host_port = new String[1];
		String[] transport = new String[1];
		int[] mode = new int[1];
		String[] realm = new String[1];
		
		// Send it back to user.
		try {
			Element service = null;
			byte[] bhmac_key = null;
			
			/* iq node construct */
			JID from = session.getDomainAsJID();
			JID to = session.getJID();
			StanzaType type = StanzaType.result;
			String id = packet.getStanzaId();

			Element iq = new Element("iq",
					new String[] {"from", "to", "type", "id"},
					new String[] {from.toString(), to.toString(), type.toString(), id});
			
			/* services node construct */
			Element services = new Element("services", new String[]{ "xmlns" }, XMLNSS);
			iq.addChild(services);
			
			/* get and contruct stun parameters */
			String stun_url = System.getProperty(GEN_STUN_URI_PROP_KEY);
			if (0 != getStunProperty(stun_url, host_name, host_port, transport)) {
				System.out.println("get stun error");
				return null;
			}
			/* service child node construct */
			services.addChild(service = new Element("service"));
			
			/* get service value */
			service.addAttribute("host", host_name[0]);
			service.addAttribute("port", host_port[0]);
			service.addAttribute("transport", transport[0]);
			service.addAttribute("type", "stun");
			
			/* get and contruct turn parameters */
			String turn_url = System.getProperty(GEN_TURN_URI_PROP_KEY);
			if (0 != getTurnProperty(turn_url, host_name, host_port, transport, realm, mode)) {
				System.out.println("get turn error");
				return null;
			}
			productTurnUserPasswd(user_id, user_name, password, mode[0]);
			
			if (TURN_MODE_COMMON == mode[0]) {
				bhmac_key = productHmacKey(stringToHex(user_name[0]), stringToHex(realm[0]), 
			              stringToHex(password[0]), SHATYPE_MD5);
				if (null == bhmac_key) {
					return null;
				}
				hmac_key[0] = hexToString(bhmac_key);
				
				/* notes: exist user_name problem */
				storeTurnUser(user_id, user_name[0], hmac_key[0]);
			}
			services.addChild(service = new Element("service"));
			
			/* get service value */
			service.addAttribute("host", host_name[0]);
			service.addAttribute("port", host_port[0]);
			service.addAttribute("transport", transport[0]);
			service.addAttribute("type", "turn");
			service.addAttribute("username", user_name[0]);
			service.addAttribute("password", password[0]);
			
			/* construct packet */
			pack_res = Packet.packetInstance(iq);
			
		} catch (NotAuthorizedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TigaseStringprepException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		return pack_res;
	}
    
	@Override
	public void process(Packet packet, XMPPResourceConnection session, NonAuthUserRepository repo,
			Queue<Packet> results, Map<String, Object> settings) throws XMPPException {
		// TODO Auto-generated method stub
		if (log.isLoggable(Level.FINEST)) {
			log.finest("Processing packet: " + packet.toString());
		}
		
		if (session == null) {
			if (log.isLoggable(Level.FINEST)) {
				log.finest("Session is null, ignoring");
			}

			return;
		} // end of if (session == null)

		// TODO BareJID
		BareJID id = session.getDomainAsJID().getBareJID();
		BareJID user_id = session.getBareJID();
		
		//session.setData(subnode, key, value);

		if (packet.getStanzaTo() != null) {
			id = packet.getStanzaTo().getBareJID();
		}
		
		try {
			// user is Authorized
			if ((packet.getPacketFrom() != null) 
				&& packet.getPacketFrom().equals(session.getConnectionId())
				&& session.isAuthorized()) {
				// get IQ attribute
				StanzaType type = packet.getType();

				/* check service package */
				Element request = packet.getElement();
				Element services = request.findChild(IQ_SERVICES);
				if (null == services) {
					results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet, "Message type is incorrect", true));
					return;
				}
				
				System.out.println("xmpp extdisco services node is ok!\n");
				
				switch (type) {
				case get: {
					System.out.println("xmpp extdisco services type is get!");

					//System.out.println(settings.get(ConfiguratorAbstract.GEN_STUN_URI_PROP).toString());
					//session.getPriority();
					/* construct message */
					Packet pack_res = respProcess(user_id, session, packet);
										
					pack_res.setPacketTo(session.getConnectionId());
					results.offer(pack_res);
					
					System.out.println("xmpp response message:" + pack_res.toString());
					
					break;
				}
				default:
					System.out.println("xmpp extdisco servies type is error !\n");
					results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet, "Message type is incorrect", true));
					
					break;
				} // end of switch (type)
			} else {
				System.out.println("xmpp extdisco messgae is error!\n");
				
				if (session.isUserId(id)) {

					// It might be a registration request from transport for
					// example...
					Packet pack_res = packet.copyElementOnly();

					pack_res.setPacketTo(session.getConnectionId());
					results.offer(pack_res);
				} else {
					results.offer(packet.copyElementOnly());
				}
			}
		} catch (NotAuthorizedException e) {
			results.offer(Authorization.NOT_AUTHORIZED.getResponseMessage(packet,
					"You are not authorized to change registration settings.\n" + e.getMessage(), true));
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


