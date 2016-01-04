package tigase.hinest;

import java.util.Map;

import javax.script.Bindings;

import tigase.conf.ConfigurationException;
import tigase.server.AbstractMessageReceiver;
import tigase.server.Packet;
import tigase.stats.StatisticsList;

import java.util.HashMap;
import java.util.Set;

import com.cloopen.rest.sdk.CCPRestSmsSDK;

public class HinestComponent extends AbstractMessageReceiver {

	private static final String PACKET_TYPES_KEY = "packet-types";
	private static final String PREPEND_TEXT_KEY = "log-prepend";

	private String[] packetTypes = { "message", "presence", "iq" };
	private String prependText = "My packet: ";

	
	//处理发送到该组件的包
	@Override
	public void processPacket(Packet packet) {

		for (String pType : packetTypes) {
			if (pType == packet.getElemName()) {
				System.out.println(prependText + packet.toString());
				phoneNumCheck();
			}
		}
	}
	
	public void phoneNumCheck(){

		HashMap<String, Object> result = null;

		//初始化SDK
		CCPRestSmsSDK restAPI = new CCPRestSmsSDK();
		
		//******************************注释*********************************************
		//*初始化服务器地址和端口                                                       *
		//*沙盒环境（用于应用开发调试）：restAPI.init("sandboxapp.cloopen.com", "8883");*
		//*生产环境（用户应用上线使用）：restAPI.init("app.cloopen.com", "8883");       *
		//*******************************************************************************
		restAPI.init("sandboxapp.cloopen.com", "8883");
		
		//******************************注释*********************************************
		//*初始化主帐号和主帐号令牌,对应官网开发者主账号下的ACCOUNT SID和AUTH TOKEN     *
		//*ACOUNT SID和AUTH TOKEN在登陆官网后，在“应用-管理控制台”中查看开发者主账号获取*
		//*参数顺序：第一个参数是ACOUNT SID，第二个参数是AUTH TOKEN。                   *
		//*******************************************************************************
		restAPI.setAccount("aaf98f894e52805a014e664a5a370f78",
				"8ff67cc49ea2421aab9a2df372beb1be");
		
		//******************************注释*********************************************
		//*初始化应用ID                                                                 *
		//*测试开发可使用“测试Demo”的APP ID，正式上线需要使用自己创建的应用的App ID     *
		//*应用ID的获取：登陆官网，在“应用-应用列表”，点击应用名称，看应用详情获取APP ID*
		//*******************************************************************************
		restAPI.setAppId("aaf98f894e52805a014e666869f20fa4");
		
		
		//******************************注释****************************************************************
		//*调用发送模板短信的接口发送短信                                                                  *
		//*参数顺序说明：                                                                                  *
		//*第一个参数:是要发送的手机号码，可以用逗号分隔，一次最多支持100个手机号                          *
		//*第二个参数:是模板ID，在平台上创建的短信模板的ID值；测试的时候可以使用系统的默认模板，id为1。    *
		//*系统默认模板的内容为“【云通讯】您使用的是云通讯短信模板，您的验证码是{1}，请于{2}分钟内正确输入”*
		//*第三个参数是要替换的内容数组。																														       *
		//**************************************************************************************************
		
		//**************************************举例说明***********************************************************************
		//*假设您用测试Demo的APP ID，则需使用默认模板ID 1，发送手机号是13800000000，传入参数为6532和5，则调用方式为           *
		//*result = restAPI.sendTemplateSMS("13800000000","1" ,new String[]{"6532","5"});																		  *
		//*则13800000000手机号收到的短信内容是：【云通讯】您使用的是云通讯短信模板，您的验证码是6532，请于5分钟内正确输入     *
		//*********************************************************************************************************************
		
		result = restAPI.sendTemplateSMS("18601758932", "1", new String[] {
				String.valueOf(Math.random() * 10000), "5" });

		System.out.println("SDKTestGetSubAccounts result=" + result);
		if ("000000".equals(result.get("statusCode"))) {
			// 正常返回输出data包体信息（map）
			HashMap<String, Object> data = (HashMap<String, Object>) result
					.get("data");
			Set<String> keySet = data.keySet();
			for (String key : keySet) {
				Object object = data.get(key);
				System.out.println(key + " = " + object);
			}
		} else {
			// 异常返回输出错误码和错误信息
			System.out.println("错误码=" + result.get("statusCode") + " 错误信息= "
					+ result.get("statusMsg"));
		}
	}

	//配置相关
	@Override
	public Map<String, Object> getDefaults(Map<String, Object> params) {
		Map<String, Object> defs = super.getDefaults(params);
		defs.put(PACKET_TYPES_KEY, packetTypes);
		defs.put(PREPEND_TEXT_KEY, prependText);

		return defs;
	}

	@Override
	public void setProperties(Map<String, Object> props)
			throws ConfigurationException {
		super.setProperties(props);
		if (props.get(PACKET_TYPES_KEY) != null) {
			packetTypes = (String[]) props.get(PACKET_TYPES_KEY);
		}
		// Make sure we can compare element names by reference
		// instead of String content
		for (int i = 0; i < packetTypes.length; i++) {
			packetTypes[i] = packetTypes[i].intern();
		}
		if (props.get(PREPEND_TEXT_KEY) != null) {
			prependText = (String) props.get(PREPEND_TEXT_KEY);
		}

	}

	// 执行周期性任务
	@Override
	public synchronized void everySecond() {
		super.everySecond();
//		System.out.println("everySecond");

	}

	@Override
	public synchronized void everyMinute() {
		super.everyMinute();
		System.out.println("everyMinute=========================");

	}

	@Override
	public synchronized void everyHour() {
		super.everyHour();
		System.out.println("everyHour@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	}
	
	//服务发现
	@Override
	public String getDiscoDescription() {
	  return "Hinest Service";
	}
	 
	@Override
	public String getDiscoCategoryType() {
	  return "hinest";
	}
	
	// 统计信息
	@Override
	public void getStatistics(StatisticsList list) {
		super.getStatistics(list);
		// list.add(getName(), "Spam messages found", totalSpamCounter,
		// Level.INFO);
		// list.add(getName(), "All messages processed", messagesCounter,
		// Level.FINER);
		// if (list.checkLevel(Level.FINEST)) {
		// // 可以把那些非常消耗系统资源的统计数据产生代码写在下面
		// }
	}
	
	//脚本支持
	@Override
	public void initBindings(Bindings binds) {
	  super.initBindings(binds);
//	  binds.put(BAD_WORDS_VAR, badWords);
//	  binds.put(WHITE_LIST_VAR, whiteList);
	}

}
