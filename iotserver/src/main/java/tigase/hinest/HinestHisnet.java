package tigase.hinest;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.logging.Level;
import java.util.logging.Logger;

import tigase.db.NonAuthUserRepository;
import tigase.db.TigaseDBException;
import tigase.db.UserNotFoundException;
import tigase.server.Iq;
import tigase.server.Packet;
import tigase.server.Priority;
import tigase.util.TigaseStringprepException;
import tigase.xml.DomBuilderHandler;
import tigase.xml.Element;
import tigase.xml.SimpleParser;
import tigase.xml.SingletonFactory;
import tigase.xmpp.Authorization;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;
import tigase.xmpp.StanzaType;
import tigase.xmpp.XMPPException;
import tigase.xmpp.XMPPProcessor;
import tigase.xmpp.XMPPProcessorIfc;
import tigase.xmpp.XMPPResourceConnection;
import tigase.xmpp.impl.roster.RosterAbstract;
import tigase.xmpp.impl.roster.RosterFactory;

public class HinestHisnet extends XMPPProcessor implements XMPPProcessorIfc{
	
	private static Logger log = Logger.getLogger(HinestHisnet.class.getName());
	private static final String HISNET = "hisnet";
	private static final String[][] ELEMENTS = { {"iq",HISNET} };
	private static final String[] XMLNSS = { "hinest:iq:hisnet" };
	public static final String ID = "hinest:iq:hisnet";
	public static final String DEV_DOMAIN_KEY = "hinest-dev-domain";
	public static final String USR_DOMAIN_KEY = "hinest-usr-domain";
	public static final String CHECKUPDATE_URL_KEY = "checkupdate-url";
	public static final String GETUPDATE_URL_KEY = "getupdate-url";
	public static boolean initConfig = false;
	private static String DEV_DOMAIN = "dev.hinest";
	private static String USR_DOMAIN = "usr.hinest";
	private static String CHECKUPDATE_URL = null;
	private static String GETUPDATE_URL = null;
	
	protected RosterAbstract roster_util = getRosterUtil();
	protected SimpleParser parser = SingletonFactory.getParserInstance();

	private static final String[] IQ_HISNET_ONLINENOTIFY_BINDSTATE= { Iq.ELEM_NAME,HISNET, "onlinenotify","bindstate"};
	private static final String[] IQ_HISNET_ONLINENOTIFY_MAINVERSION= { Iq.ELEM_NAME,HISNET, "onlinenotify","mainversion"};
	private static final String[] IQ_HISNET_ONLINENOTIFY_BAKVERSION= { Iq.ELEM_NAME,HISNET, "onlinenotify","bakversion"};
	private static final String[] IQ_HISNET_ONLINENOTIFY= { Iq.ELEM_NAME,HISNET, "onlinenotify"};
	private static final String[] IQ_HISNET_UPDATE= { Iq.ELEM_NAME,HISNET, "update"};
	private static final String[] IQ_HISNET_UPDATE_MAINVERSION= { Iq.ELEM_NAME,HISNET, "update","mainversion"};
	private static final String[] IQ_HISNET_GETCURDEVVER= { Iq.ELEM_NAME,HISNET, "getcurdevver"};
	
	protected static RosterAbstract getRosterUtil() {
		return RosterFactory.getRosterImplementation(true);
	}
	
	@Override
	public String id() {
		return ID;
	}

	@Override
	public void process(Packet packet, XMPPResourceConnection session,
			NonAuthUserRepository repo, Queue<Packet> results,
			Map<String, Object> settings) throws XMPPException{
		
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
			if(settings.containsKey(CHECKUPDATE_URL_KEY)){
				CHECKUPDATE_URL = (String) settings.get(CHECKUPDATE_URL_KEY);
			}
			if(settings.containsKey(GETUPDATE_URL_KEY)){
				GETUPDATE_URL = (String) settings.get(GETUPDATE_URL_KEY);
			}
			initConfig = true;
		}

		HinestLog.debug("dev-domain:" + DEV_DOMAIN);
		HinestLog.debug("usr-domain:" + USR_DOMAIN);
		HinestLog.debug("checkupdate-url:" + CHECKUPDATE_URL);
		HinestLog.debug("getupdate-url:" + GETUPDATE_URL);
		
		HinestLog.debug("hisnet:" + packet.toString());
	
		if (session == null) {
			if (log.isLoggable(Level.FINE)) {
				log.log(Level.FINE, "Session is null, ignoring packet: {0}", packet);
			}

			return;
		}
		
		if (!session.isAuthorized()) {
			if (log.isLoggable(Level.FINE)) {
				log.log(Level.FINE, "Session is not authorized, ignoring packet: {0}", packet);
			}

			return;
		}
		
		
		Element request = packet.getElement();
		StanzaType type = packet.getType();
		
		try{
		
			switch (type) {		
				case get: {

					if((packet.getStanzaTo()!=null) && packet.getStanzaTo().getBareJID().toString().equals(USR_DOMAIN)
							&& (packet.getStanzaFrom()!= null ) && packet.getStanzaFrom().getDomain().equals(USR_DOMAIN)
							&& session.isUserId(packet.getStanzaFrom().getBareJID())){
						
						String devId;
						BareJID devJid;
						String mainVersion;
						String bakVersion;
						
						devId = request.getAttributeStaticStr(IQ_HISNET_GETCURDEVVER, "deviceid");
						
						//获取版本号
						if(null != devId){
							devJid = BareJID.bareJIDInstance(devId);
							mainVersion = repo.getPublicData(devJid, HISNET, "mainVersion", "");
							HinestLog.debug("mainVersion:"+mainVersion);
							
							Element hisnet = new Element("hisnet");
							hisnet.setXMLNS(ID);
							hisnet.addChild(new Element("mainversion",mainVersion));
									
							results.offer(packet.okResult(hisnet.toString(), 0));
							break;
							
						}
						
						devId = request.getAttributeStaticStr(IQ_HISNET_UPDATE, "deviceid");
						
						devJid = BareJID.bareJIDInstance(devId);
						
						HinestLog.debug("devID:"+devId);
						
						//查找设备当前版本
						mainVersion = repo.getPublicData(devJid, HISNET, "mainVersion", null);
						bakVersion = repo.getPublicData(devJid, HISNET, "bakVersion", null);
						
						HinestLog.debug("mainVersion:"+mainVersion);
						HinestLog.debug("bakVersion:"+bakVersion);
					
						
						//主备份版本号发给httpserver,获取url
						if(mainVersion!=null && bakVersion!=null){
							
							String postData="";
							try {
								postData = "deviceid="+URLEncoder.encode(devId, "UTF-8")
										+"&cur_mainversion="+URLEncoder.encode(mainVersion, "UTF-8")
										+"&cur_backupversion="+URLEncoder.encode(bakVersion, "UTF-8");
							} catch (UnsupportedEncodingException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							
							String checkupdate = getHttpXML(CHECKUPDATE_URL,postData);
							HinestLog.debug("@postData:"+postData);
							HinestLog.debug("@checkupdate:"+checkupdate);
							
							DomBuilderHandler domHandler = new DomBuilderHandler();
							
							parser.parse(domHandler, checkupdate.toCharArray(), 0, checkupdate.length());
							Queue<Element> elems  = domHandler.getParsedElements();
							String backup_version = null;
							String backup_url= null;
							String main_version= null;
							String main_description = null;
							String[] backup_version_path = {"checkupdate","backup","version"};
							String[] backup_url_path = {"checkupdate","backup","url"};
							String[] main_version_path = {"checkupdate","main","version"};
							String[] main_description_path = {"checkupdate","main","description"};
							
							for (Element el : elems) {   
								backup_version = el.getChildCDataStaticStr(backup_version_path);
								backup_url = el.getChildCDataStaticStr(backup_url_path);
								main_version = el.getChildCDataStaticStr(main_version_path);
								main_description = el.getChildCDataStaticStr(main_description_path);
							}
							
							//记录可升级的最新版本
							session.setPublicData(HISNET, "newMainVersion", main_version);
							session.setPublicData(HISNET, "newBakVersion", backup_version);
							
							if(main_version != null){
								Element hisnet = new Element("hisnet");
								hisnet.setXMLNS(ID);
								hisnet.addChild(new Element("mainversion",main_version));
								hisnet.addChild(new Element("description",main_description));
								results.offer(packet.okResult(hisnet.toString(), 0));
								break;
							}
							
						}
							
						results.offer(packet.okResult("<mainversion></mainversion>", 0));
		
					}else{
						HinestLog.debug("get ignore it~~~");				
						log.log( Level.WARNING, "igore it~",packet);		
						results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet,"iq format is incorrect", true));
					}
				
					break;
				}
				case set: {
					//packet from usr
					if((packet.getStanzaTo()!=null) && packet.getStanzaTo().getBareJID().toString().equals(USR_DOMAIN) 
							&& (packet.getStanzaFrom()!= null ) && packet.getStanzaFrom().getDomain().equals(USR_DOMAIN)
							&& session.isUserId(packet.getStanzaFrom().getBareJID())){
						
						String devId;
						String mainVersion;
						String newMainVersion;
						String newBackupVersion;
						
						devId = request.getAttributeStaticStr(IQ_HISNET_UPDATE, "deviceid");
						mainVersion = request.getChildCDataStaticStr(IQ_HISNET_UPDATE_MAINVERSION);
						
						HinestLog.debug("devId:"+devId);
						HinestLog.debug("mainVersion:"+mainVersion);
						
						BareJID devJid = BareJID.bareJIDInstance(devId);
						
						newMainVersion = repo.getPublicData(devJid, HISNET, "newMainVersion", "");
						newBackupVersion = repo.getPublicData(devJid, HISNET, "newBackupVersion", "");
						
						HinestLog.debug("newMainVersion:" + newMainVersion);
						HinestLog.debug("newBackupVersion:" + newBackupVersion);
						
						String postData="";
						try {
							postData = "new_mainversion="+URLEncoder.encode(newMainVersion, "UTF-8")
									+"&old_backupversion="+URLEncoder.encode(newBackupVersion, "UTF-8");
						} catch (UnsupportedEncodingException e) {
							e.printStackTrace();
						}
						String getUpdateUrl = getHttpXML(GETUPDATE_URL,postData);
						HinestLog.debug("@postData:"+postData);
						HinestLog.debug("@getUpdateUrl:"+getUpdateUrl);
						
						DomBuilderHandler domHandler = new DomBuilderHandler();
						
						parser.parse(domHandler, getUpdateUrl.toCharArray(), 0, getUpdateUrl.length());
						Queue<Element> elems  = domHandler.getParsedElements();
						String backup_version = null;
						String backup_url= null;
						String main_version= null;
						String main_url=null;
						String[] backup_version_path = {"upgrade-packages","backup","version"};
						String[] backup_url_path = {"upgrade-packages","backup","url"};
						String[] main_version_path = {"upgrade-packages","main","version"};
						String[] main_url_path = {"upgrade-packages","main","url"};
						
						for (Element el : elems) {   
							backup_version = el.getChildCDataStaticStr(backup_version_path);
							backup_url = el.getChildCDataStaticStr(backup_url_path);
							main_version = el.getChildCDataStaticStr(main_version_path);
							main_url = el.getChildCDataStaticStr(main_url_path);
						}
						
						Element msg = null;
			    		Packet  result  = null;

			    		msg = new Element("message");
			    		msg.setAttribute("from", DEV_DOMAIN);
			    		msg.setXMLNS("jabber:client");
			    		msg.setAttribute("to", devId);
			    		String body = "{\"cmd\":\"update\",\"type\":\"set\",\"deviceid\":\""+devId
			    				+"\",\"mainurl\":\""+main_url+"\",\"bakurl\":\""+backup_url+"\"}";
			    		msg.addChild(new Element("body", body));
			    		
			    		try {
			    			result = Packet.packetInstance(msg);
			    			if (log.isLoggable(Level.FINEST)) {
			    				log.log(Level.FINEST, "Sending presence info: {0}", result);
			    			}
			    			HinestLog.debug("Sending presence info: "+result);
			    			results.offer(result);
			    			
			    		} catch (TigaseStringprepException ex) {  
			    			log.log(Level.FINE,
			    					"Packet stringprep addressing problem, skipping presence send: {0}", msg);
			    		}
			    		
			    		Element hisnet = new Element("hisnet");
			    		hisnet.setXMLNS(ID);
			    		results.offer(packet.okResult(hisnet, 0));
						
					}
					//packet from dev
					else if((packet.getStanzaTo()!=null) && packet.getStanzaTo().getBareJID().toString().equals(DEV_DOMAIN) 
							&& (packet.getStanzaFrom()!= null ) && packet.getStanzaFrom().getDomain().equals(DEV_DOMAIN)
							&& session.isUserId(packet.getStanzaFrom().getBareJID())){
						
						String bindState;
						String mainVersion;
						String bakVersion;
						String devId;
	
						devId = request.getAttributeStaticStr(IQ_HISNET_ONLINENOTIFY, "deviceid");
						bindState = request.getChildCDataStaticStr(IQ_HISNET_ONLINENOTIFY_BINDSTATE);
						mainVersion = request.getChildCDataStaticStr(IQ_HISNET_ONLINENOTIFY_MAINVERSION);
						bakVersion = request.getChildCDataStaticStr(IQ_HISNET_ONLINENOTIFY_BAKVERSION);
						
						HinestLog.debug("devId:"+devId);
						HinestLog.debug("bindState:"+bindState);
						HinestLog.debug("mainVersion:"+mainVersion);
						HinestLog.debug("bakVersion:"+bakVersion);
						
						//参数检查+储存主备份版本号
						if(devId!=null && devId.equals(packet.getStanzaFrom().getBareJID().toString()) && bindState!=null 
								&&(bindState.trim().equals("false")||bindState.trim().equals("true"))
								&& mainVersion!=null && bakVersion!=null){
							session.setPublicData(HISNET, "mainVersion", mainVersion);
							session.setPublicData(HISNET, "bakVersion" , bakVersion);
						}else{
							results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet,"Message type is incorrect", true));
							break;
						}
						
						if(bindState.trim().equals("false")){
							//解除绑定
							String owner = null;
							JID[] buddies = roster_util.getBuddies(session,RosterAbstract.SUB_BOTH);
							
							if(buddies!=null && buddies.length>=1){
								owner = buddies[0].getBareJID().toString();
								//session.setPublicData(HISNET, "owner", owner);
								HinestLog.debug("owner:"+owner);
								
								//解绑定,删除dev的owner
								roster_util.removeBuddy(session, buddies[0]);
									
								//解除绑定owner
								Element presence_unsubscribe = null;
					    		Packet  result_unsubscribe  = null;

					    		presence_unsubscribe = new Element("presence");
					    		presence_unsubscribe.setAttribute("type", StanzaType.unsubscribe.toString());
					    		presence_unsubscribe.setAttribute("from", packet.getStanzaFrom().toString());
					    		presence_unsubscribe.setXMLNS("jabber:client");
					    		presence_unsubscribe.setAttribute("to", owner);
					    		
					    		try {
					    			result_unsubscribe = Packet.packetInstance(presence_unsubscribe);
					    			if (log.isLoggable(Level.FINEST)) {
					    				log.log(Level.FINEST, "Sending presence info: {0}", result_unsubscribe);
					    			}
					    			HinestLog.debug("Sending presence info: "+result_unsubscribe);
					    			results.offer(result_unsubscribe);
					    			
					    		} catch (TigaseStringprepException ex) {
					    			log.log(Level.FINE,
					    					"Packet stringprep addressing problem, skipping presence send: {0}", presence_unsubscribe);
					    		}
								
								
								Element presence_unsubscribed = null;
					    		Packet  result_unsubscribed   = null;

					    		presence_unsubscribed = new Element("presence");
					    		presence_unsubscribed.setAttribute("type", StanzaType.unsubscribed.toString());
					    		presence_unsubscribed.setAttribute("from", packet.getStanzaFrom().toString());
					    		presence_unsubscribed.setXMLNS("jabber:client");
					    		presence_unsubscribed.setAttribute("to", owner);
					    		
					    		try {
					    			result_unsubscribed = Packet.packetInstance(presence_unsubscribed);
					    			if (log.isLoggable(Level.FINEST)) {
					    				log.log(Level.FINEST, "Sending presence info: {0}", result_unsubscribed);
					    			}
					    			HinestLog.debug("Sending presence info: "+result_unsubscribed);
					    			
					    			results.offer(result_unsubscribed);
					    			
					    		} catch (TigaseStringprepException ex) {
					    			log.log(Level.FINE,
					    					"Packet stringprep addressing problem, skipping presence send: {0}", presence_unsubscribed);
					    		}

							}
	
							results.offer(packet.okResult((String) null, 0));
							
						}else{
							
							//主备份版本号发给httpserver,获取url,升级备份系统发送通知给ipc，升级主系统发送通知给owner
							String postData="";
							try {
								postData = "deviceid="+URLEncoder.encode(devId, "UTF-8")
										+"&cur_mainversion="+URLEncoder.encode(mainVersion, "UTF-8")
										+"&cur_backupversion="+URLEncoder.encode(bakVersion, "UTF-8");
							} catch (UnsupportedEncodingException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							String checkupdate = getHttpXML(CHECKUPDATE_URL,postData);
							HinestLog.debug("@postData:"+postData);
							HinestLog.debug("@checkupdate:"+checkupdate);
							
							DomBuilderHandler domHandler = new DomBuilderHandler();
							
							parser.parse(domHandler, checkupdate.toCharArray(), 0, checkupdate.length());
							Queue<Element> elems  = domHandler.getParsedElements();
							String backup_version = null;
							String backup_url= null;
							String main_version= null;
							String main_description = null;
							String[] backup_version_path = {"checkupdate","backup","version"};
							String[] backup_url_path = {"checkupdate","backup","url"};
							String[] main_version_path = {"checkupdate","main","version"};
							String[] main_description_path = {"checkupdate","main","description"};
							
							for (Element el : elems) {
								backup_version = el.getChildCDataStaticStr(backup_version_path);
								backup_url = el.getChildCDataStaticStr(backup_url_path);
								main_version = el.getChildCDataStaticStr(main_version_path);
								main_description = el.getChildCDataStaticStr(main_description_path);
							}
							
							//记录可以升级的最新版本
							session.setPublicData(HISNET, "newMainVersion", main_version);
							session.setPublicData(HISNET, "newBakVersion", backup_version);
							
							if(main_version!=null){
								//通知owner升级
										
								JID[] buddies = roster_util.getBuddies(session,RosterAbstract.SUB_BOTH);
								String owner;
								
								if(buddies!=null && buddies.length>=1){
									owner = buddies[0].getBareJID().toString();
									
									Element msg = null;
						    		Packet  result  = null;

						    		msg = new Element("message");
						    		msg.setAttribute("from", packet.getStanzaFrom().toString());
						    		msg.setXMLNS("jabber:client");
						    		msg.setAttribute("to", owner);
						    		//msg.addChild(new Element("body", "{\"deviceid\":\""+devId+"\",\"version\":\""+main_version+"\"}"));
						    		msg.addChild(new Element("body", "{\"deviceid\":\""+devId+"\",\"version\":\""+main_version+"\",\"description\":"+main_description+"\"}"));
						    		
						    		try {
						    			result = Packet.packetInstance(msg);
						    			if (log.isLoggable(Level.FINEST)) {
						    				log.log(Level.FINEST, "Sending presence info: {0}", result);
						    			}
						    			HinestLog.debug("Sending presence info: "+result);
						    			results.offer(result);
						    			
						    		} catch (TigaseStringprepException ex) {
						    			log.log(Level.FINE,
						    					"Packet stringprep addressing problem, skipping presence send: {0}", msg);
						    		}
									
								}
								results.offer(packet.okResult((String) null, 0));
							}else{
								
								if(backup_version!=null){
									//悄悄升级备份系统
									results.offer(packet.okResult("<updatebackup><version>"+backup_version
											+"</version><url>"+backup_url+"</url></updatebackup>", 0));
								}else{
									//安静的做一个美男子~
									
									results.offer(packet.okResult((String) null, 0));
								}
							}
						}
					}else{
						
						HinestLog.debug("set ignore it~~~");
						log.log( Level.WARNING, "igore it~",packet);
						results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet,"iq format is incorrect", true));
					}
						
					break;
				}
				case result: {
					// It might be a registration request from transport for
					// example...
					Packet pack_res = packet.copyElementOnly();
	
					pack_res.setPacketTo(session.getConnectionId());
					results.offer(pack_res);
				}
				default: {
					results.offer(Authorization.BAD_REQUEST.getResponseMessage(packet,"Message type is incorrect", true));
					break;
				}
			}
		}catch (UserNotFoundException e) {
			results.offer(Authorization.ITEM_NOT_FOUND.getResponseMessage(packet,
					"User not found", true));
		}catch (TigaseStringprepException ex) {
			results.offer(Authorization.JID_MALFORMED.getResponseMessage(
					packet,
					"Incorrect user name, stringprep processing failed.", true));
		}catch (TigaseDBException ex) {
			log.warning("Database problem, please contact admin: " + ex);
			results.offer(Authorization.INTERNAL_SERVER_ERROR.getResponseMessage(packet,
					"Database access problem, please contact administrator.", true));
		}
	}
		
	public String getHttpXML(String url,String postData) {
		
		URL myFileURL;
		HttpURLConnection conn = null;
		BufferedReader reader = null;
		String result = "";
		
		try {
			String encoding="UTF-8";
			byte[] data = postData.getBytes(encoding);
			myFileURL = new URL(url);
			conn = (HttpURLConnection) myFileURL.openConnection();
			// 设置超时时间为，单位毫秒。conn.setConnectionTiem(0);表示没有时间限制
			conn.setConnectTimeout(5*1000);
			conn.setRequestMethod("POST");
			conn.setDoInput(true);
			conn.setDoOutput(true);
			conn.setUseCaches(false);
			//application/x-javascript 
			//text/xml->xml数据 
			//application/x-javascript->json对象 
			//application/x-www-form-urlencoded->表单数据
			//conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded;charset="+encoding);
			conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
	        conn.setRequestProperty("Content-Length", String.valueOf(data.length)); 
			conn.connect();
			DataOutputStream out = new DataOutputStream(conn.getOutputStream());  
	        out.writeBytes(postData); //写入请求的字符串  
	        out.flush();  
	        out.close();
	        
	        if(conn.getResponseCode() ==200) {  
				InputStream in = conn.getInputStream();
				reader = new BufferedReader(new InputStreamReader(in));
				StringBuffer strBuffer = new StringBuffer("");
				String line = null;
				while ((line = reader.readLine()) != null) {
					strBuffer.append(line);
				}
				result = strBuffer.toString();
				in.close();
	        }
	        	
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (conn != null) {
				conn.disconnect(); // 中断连接
			}
		}
		return result;
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
