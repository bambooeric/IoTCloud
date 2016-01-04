package tigase.hinest;

import java.util.HashMap;
import java.util.Random;
import java.util.Set;

import com.cloopen.rest.sdk.CCPRestSmsSDK;

public class CheckCodeTool {

	public static final int CHECK_CODE_LENGTH = 6;
	public static final int CHECK_CODE_TIMEOUT = 5;// minute

	public static String createCheckCode(int checkCodeLength) {
		String Vchar = "0,1,2,3,4,5,6,7,8,9";
		Vchar = Vchar + ",A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z";
		Vchar = Vchar.toLowerCase();
		String[] VcArray = Vchar.split(",");
		String VNum = "";
		int temp = -1;

		Random rand = new Random();
		for (int i = 1; i < checkCodeLength + 1; i++) {
			if (temp != -1) {
				rand = new Random(i * temp * System.currentTimeMillis());
			}
			int t = rand.nextInt(35);
			if (temp != -1 && temp == t) {
				return createCheckCode(checkCodeLength);
			}
			temp = t;
			VNum += VcArray[t];

		}
		return VNum;
	}

	public static boolean sendCheckCode(String phone, String checkcode) {

		HashMap<String, Object> result = null;

		// 初始化SDK
		CCPRestSmsSDK restAPI = new CCPRestSmsSDK();

		// ******************************注释*********************************************
		// *初始化服务器地址和端�?*
		// *沙盒环境（用于应用开发调试）：restAPI.init("sandboxapp.cloopen.com", "8883");*
		// *生产环境（用户应用上线使用）：restAPI.init("app.cloopen.com", "8883"); *
		// *******************************************************************************
		restAPI.init("app.cloopen.com", "8883");

		// ******************************注释*********************************************
		// *初始化主帐号和主帐号令牌,对应官网开发者主账号下的ACCOUNT SID和AUTH TOKEN *
		// *ACOUNT SID和AUTH TOKEN在登陆官网后，在“应�?管理控制台”中查看开发者主账号获取*
		// *参数顺序：第一个参数是ACOUNT SID，第二个参数是AUTH TOKEN�?*
		// *******************************************************************************
		restAPI.setAccount("aaf98f8950f4a62c0150fe5ee6f62547",
				"a54c92e5e40745a1a884312f0bd40f6a");
		
		// ******************************注释*********************************************
		// *初始化应用ID *
		// *测试开发可使用“测试Demo”的APP ID，正式上线需要使用自己创建的应用的App ID *
		// *应用ID的获取：登陆官网，在“应�?应用列表”，点击应用名称，看应用详情获取APP ID*
		// *******************************************************************************
		restAPI.setAppId("aaf98f8950f4a62c0150fe5f416a2549");
		
		// ******************************注释****************************************************************
		// *调用发送模板短信的接口发送短�?*
		// *参数顺序说明�?*
		// *第一个参�?是要发送的手机号码，可以用逗号分隔，一次最多支�?00个手机号 *
		// *第二个参�?是模板ID，在平台上创建的短信模板的ID值；测试的时候可以使用系统的默认模板，id�?�?*
		// *系统默认模板的内容为“【云通讯】您使用的是云通讯短信模板，您的验证码是{1}，请于{2}分钟内正确输入�?
		// *第三个参数是要替换的内容数组�?*
		// **************************************************************************************************

		// **************************************举例说明***********************************************************************
		// *假设您用测试Demo的APP ID，则需使用默认模板ID 1，发送手机号�?3800000000，传入参数为6532�?，则调用方式�?
		// *
		// *result = restAPI.sendTemplateSMS("13800000000","1" ,new
		// String[]{"6532","5"}); *
		// *�?3800000000手机号收到的短信内容是：【云通讯】您使用的是云通讯短信模板，您的验证码�?532，请�?分钟内正确输�?*
		// *********************************************************************************************************************
		result = restAPI.sendTemplateSMS(phone, "35646", new String[] { checkcode,
				String.valueOf(CHECK_CODE_TIMEOUT) });

		HinestLog.debug("SDKTestGetSubAccounts result=" + result);

		if ("000000".equals(result.get("statusCode"))) {
			// 正常返回输出data包体信息（map�?
			HashMap<String, Object> data = (HashMap<String, Object>) result.get("data");
			Set<String> keySet = data.keySet();
			for (String key : keySet) {
				Object object = data.get(key);
				HinestLog.debug(key + " = " + object);
			}
			return true;
		} else {
			// 异常返回输出错误码和错误信息
			HinestLog.debug("错误�?" + result.get("statusCode") + " 错误信息= "
					+ result.get("statusMsg"));
		}
		return false;
	}

}
