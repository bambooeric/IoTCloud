package tigase.hinest;

public class CheckInfoNode {

	private String phone;
	private String checkcode;
	private long createTime;

	private CheckInfoNode next;

	public CheckInfoNode(String phone, String checkcode, long createTime) {
		this.phone = phone;
		this.checkcode = checkcode;
		this.createTime = createTime;
	}

	public String getPhone() {
		return phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getCheckcode() {
		return checkcode;
	}

	public void setCheckcode(String checkcode) {
		this.checkcode = checkcode;
	}

	public long getCreateTime() {
		return createTime;
	}

	public void setCreateTime(long createTime) {
		this.createTime = createTime;
	}

	public CheckInfoNode getNext() {
		return next;
	}

	public void setNext(CheckInfoNode next) {
		this.next = next;
	}
	
}