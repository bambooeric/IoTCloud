package tigase.hinest;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Queue;
import java.util.Random;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.cloopen.rest.sdk.CCPRestSmsSDK;

import tigase.db.NonAuthUserRepository;
import tigase.db.TigaseDBException;
import tigase.server.Iq;
import tigase.server.Packet;
import tigase.util.TigaseStringprepException;
import tigase.xml.Element;
import tigase.xml.XMLUtils;
import tigase.xmpp.Authorization;
import tigase.xmpp.BareJID;
import tigase.xmpp.StanzaType;
import tigase.xmpp.XMPPException;
import tigase.xmpp.XMPPProcessor;
import tigase.xmpp.XMPPProcessorIfc;
import tigase.xmpp.XMPPResourceConnection;

public class HinestResetPwd extends XMPPProcessor implements XMPPProcessorIfc {

	private static Logger log = Logger.getLogger(HinestResetPwd.class
			.getName());
	private static final String[][] ELEMENTS = { Iq.IQ_QUERY_PATH };
	private static final String[] IQ_QUERY_USERNAME_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "username" };
	private static final String[] IQ_QUERY_PASSWORD_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "password" };
	private static final String[] IQ_QUERY_EMAIL_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "email" };
	private static final String[] IQ_QUERY_PHONE_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "phone" }; // linlinno
	private static final String[] IQ_QUERY_CHECKCODE_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "checkcode" };
	private static final String[] IQ_QUERY_GETCHECKCODE_PATH = { Iq.ELEM_NAME,Iq.QUERY_NAME, "getcheckcode" };
	private static final String[] XMLNSS = { "hinest:iq:resetpwd" };
	public static final String ID = "hinest:iq:resetpwd";
	private static final int MAX_CHECKINFOLIST_SIZE = 1000;
	private CheckInfoList checkInfoList;
	public static boolean initConfig = false;
	public static final String DEV_DOMAIN_KEY = "hinest-dev-domain";
	public static final String USR_DOMAIN_KEY = "hinest-usr-domain";
	private static String DEV_DOMAIN = "dev.hinest";
	private static String USR_DOMAIN = "usr.hinest";

	@Override
	public String id() {
		return ID;
	}

	@Override
	public void process(Packet packet, XMPPResourceConnection session,
			NonAuthUserRepository repo, Queue<Packet> results,
			Map<String, Object> settings) throws XMPPException {

		if (log.isLoggable(Level.FINEST)) {
			log.finest("Processing packet: " + packet.toString());
		}

		if(!initConfig && settings!=null){
			if(settings.containsKey(DEV_DOMAIN_KEY)){
				DEV_DOMAIN = (String) settings.get(DEV_DOMAIN_KEY);
			}
			if(settings.containsKey(USR_DOMAIN_KEY)){
				USR_DOMAIN = (String) settings.get(USR_DOMAIN_KEY);
			}
		}
		
		HinestLog.debug("resetpwd:" + packet.toString());

		// linlinno
		if (checkInfoList == null) {
			checkInfoList = new CheckInfoList();
		} else {
			if (checkInfoList.getSize() > MAX_CHECKINFOLIST_SIZE) {
				checkInfoList.deleteExpiredNode(System.currentTimeMillis()
						- 1000 * 60 * CheckCodeTool.CHECK_CODE_TIMEOUT);
			}
		}

		if (session == null) {
			if (log.isLoggable(Level.FINEST)) {
				log.finest("Session is null, ignoring");
			}

			return;
		} // end of if (session == null)

		BareJID id = session.getDomainAsJID().getBareJID();

		if (packet.getStanzaTo() != null) {
			id = packet.getStanzaTo().getBareJID();
		}

		try {

			if ((packet.getPacketFrom() != null)
					&& packet.getPacketFrom().equals(session.getConnectionId())
					&& (!session.isAuthorized() || (session.isUserId(id) || session
							.isLocalDomain(id.toString(), false)))) {

				Element request = packet.getElement();
				Authorization result = Authorization.NOT_AUTHORIZED;
				StanzaType type = packet.getType();

				switch (type) {
				case set: {

					String user_name;
					String password;
//					String email;
					String phone;
					String check_code;

					user_name = request.getChildCDataStaticStr(IQ_QUERY_USERNAME_PATH);
					password = request.getChildCDataStaticStr(IQ_QUERY_PASSWORD_PATH);
//					email = request.getChildCDataStaticStr(IQ_QUERY_EMAIL_PATH);
//					phone = request.getChildCDataStaticStr(IQ_QUERY_PHONE_PATH);// linlinno
					check_code = request.getChildCDataStaticStr(IQ_QUERY_CHECKCODE_PATH);

					String pass_enc = null;
					if (null != password) {
						pass_enc = XMLUtils.unescape(password);
					}

					HinestLog.debug("usrname:" + user_name);
					HinestLog.debug("passwd:" + pass_enc);
//					HinestLog.debug("phone:" + phone);
//					HinestLog.debug("email:" + email);
					HinestLog.debug("checkcode:" + check_code);

					Map<String, String> reg_params = new LinkedHashMap<String, String>();
//					if ((email != null) && !email.trim().isEmpty()) {
//						reg_params.put("email", email);
//					}
//					if ((phone != null) && !phone.trim().isEmpty()) {
//						reg_params.put("phone", phone);
//					}

					// 检查验证码to do
					HinestLog.debug("check check code~~~~to do");

					BareJID to = packet.getStanzaTo().getBareJID();

					HinestLog.debug("register set:" + to.getDomain());
					HinestLog.debug("auth statte:"
							+ session.getAuthState().getErrorCode());

					if (session.getAuthState() != Authorization.AUTHORIZED&& (to != null)&& to.getDomain().equals(USR_DOMAIN)) {
						// user create new account
						BareJID user = BareJID.bareJIDInstance(user_name + "@"+ USR_DOMAIN);
						phone = session.getDataSimple(user, "phone", null);
						
						Map<String, String> checkInfo = checkInfoList.getCheckInfo(phone, System.currentTimeMillis()- 1000 * 60 * CheckCodeTool.CHECK_CODE_TIMEOUT);
						checkInfoList.displayAllNodes();
						if (checkInfo != null) {

							String checkCode = checkInfo.get("checkCode");
							// 检查验证码
							if (checkCode.equals(check_code)) {
								result = session.updatePwd(user,pass_enc);

							} else {
								result = Authorization.CHECKCODE_CHECK_FAIL;
							}

						} else {
							result = Authorization.CHECKCODE_CHECK_FAIL;
						}
					}
					
					if (result == Authorization.AUTHORIZED) {
						results.offer(result.getResponseMessage(packet, null, false));
					} else {
						results.offer(result.getResponseMessage(packet, "Unsuccessful registration attempt", true));
					}
					
					break;
				}
				case get:{
										
					boolean getCheckCode = request.findChildStaticStr(IQ_QUERY_GETCHECKCODE_PATH) != null;
					BareJID to = packet.getStanzaTo().getBareJID();

					if (getCheckCode && to.getDomain().equals(USR_DOMAIN)) {

						String username = request.getChildCDataStaticStr(IQ_QUERY_GETCHECKCODE_PATH);

						HinestLog.debug("user:" + username);
						HinestLog.debug("to:" + to.getDomain());

						BareJID user = BareJID.bareJIDInstance(username + "@"+ USR_DOMAIN);
						String phone = session.getDataSimple(user, "phone", null);

						if (null != phone) {

							String checkCode = CheckCodeTool.createCheckCode(CheckCodeTool.CHECK_CODE_LENGTH);
							HinestLog.debug(packet.toString());

							//boolean ret = CheckCodeTool.sendCheckCode(phone,checkCode);
						    boolean ret = true;
							System.out.println("phone:" + phone + ", checkcode:" + checkCode);
							if (ret) {

								// 发送成功记录电话，验证码，生成时间
								HinestLog.debug("phone:" + phone);
								HinestLog.debug("checkcode:" + checkCode);
								HinestLog.debug("record phone,checkcode,createtime~~~~to do");

								checkInfoList.addFirstNode(phone, checkCode,System.currentTimeMillis());

								checkInfoList.displayAllNodes();

								results.offer(packet.okResult((String) null, 0));
								return;

							}

						}
					}
					results.offer(Authorization.CHECKCODE_SEND_FAIL.getResponseMessage(packet,"Send check code fail", true));
					break;
				}
				case result: {
					// It might be a registration request from transport for
					// example...
					Packet pack_res = packet.copyElementOnly();

					pack_res.setPacketTo(session.getConnectionId());
					results.offer(pack_res);
				}
				default:

					results.offer(Authorization.BAD_REQUEST.getResponseMessage(
							packet, "Message type is incorrect", true));

					break;

				}

			}

		} catch (TigaseStringprepException ex) {
			results.offer(Authorization.JID_MALFORMED.getResponseMessage(
					packet,
					"Incorrect user name, stringprep processing failed.", true));
		} catch (TigaseDBException e) {
			log.warning("Database problem: " + e);
			results.offer(Authorization.INTERNAL_SERVER_ERROR
					.getResponseMessage(
							packet,
							"Database access problem, please contact administrator.",
							true));
		} // end of try-catch

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
