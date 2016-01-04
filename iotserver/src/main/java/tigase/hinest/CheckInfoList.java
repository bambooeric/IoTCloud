package tigase.hinest;

import java.util.HashMap;
import java.util.Map;

public class CheckInfoList {

	private CheckInfoNode first;
	private int size;
	
	public int getSize() {
		return size;
	}
	
	public CheckInfoList() {
		this.first = null;
		this.size = 0;
	}

	// 头插法
	public void addFirstNode(String phone, String checkCode, long createTime) {
		CheckInfoNode node = new CheckInfoNode(phone, checkCode, createTime);
		node.setNext(first);
		first = node;
		size++;
	}

	// 查找checkcode
	public Map<String, String> getCheckInfo(String phone, long expiredTime) {

		CheckInfoNode current = first;

		while (current != null) {

			if (current.getCreateTime() > expiredTime) {
				if (current.getPhone().equals(phone)) {
					Map<String, String> info = new HashMap<String, String>();
					info.put("phone", current.getPhone());
					info.put("checkCode", current.getCheckcode());
					info.put("createTime",
							String.valueOf(current.getCreateTime()));

					return info;
				}
			} else {
				return null;
			}
			current = current.getNext();
		}
		return null;
	}

	// 删除过期节点
	public void deleteExpiredNode(long expiredTime) {

		CheckInfoNode current = first;
		CheckInfoNode previous = first;

		while (current != null) {
			if (current.getCreateTime() > expiredTime) {
				previous = current;
				current = current.getNext();
			} else {
				break;
			}
		}

		if (current != null) {
			deleteList(current);
			previous.setNext(null);
		}

	}

	public void deleteList(CheckInfoNode first) {
		CheckInfoNode current = first;
		CheckInfoNode previous = first;
		while (current != null) {
			previous = current;
			current = current.getNext();
			previous.setNext(null);
			size--;
		}
	}

	// 显示出所有的节点信息
	public void displayAllNodes() {
		CheckInfoNode current = first;
		int i = 0;
		while (current != null) {
			HinestLog.debug(i + " : " + current.getPhone() + " / "
					+ current.getCheckcode() + " / " + current.getCreateTime());
			current = current.getNext();
			i++;
		}
	}

}
