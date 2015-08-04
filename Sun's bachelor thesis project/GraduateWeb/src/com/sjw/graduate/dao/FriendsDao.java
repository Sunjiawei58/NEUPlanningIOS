package com.sjw.graduate.dao;

import java.sql.ResultSet;
import java.util.ArrayList;

import com.sjw.gradute.entity.Message;
import com.sjw.gradute.entity.User;
import com.sjw.gradute.entity.Friends;
public class FriendsDao extends DBOper {

	
	public int addUser(Friends friends){
		String sql="INSERT INTO friends(me,friend)" +
				       "values(?,?)";
		String[] params={friends.getMe(),friends.getFriend()};
//		System.out.println(friends.getFriend());
		int result=this.executeUpdate(sql, params);
		return result;
		}
	
	public ArrayList<Friends> searchFriends(String server,String db,String user,String pwd,String friend)
	{
		String[] para={friend};
		System.out.println("----------------------------------");
		System.out.println("服务器日志");
		System.out.println("用户"+friend+"请求登录...\n");
		//System.out.println(password);
		//��ѯ����
		String sql="SELECT * FROM friends WHERE friend=?";
		//friend 还是自己，传的参数还是me的参数，因为要找到接收者是自己的记录
	    ArrayList<Friends> list=new ArrayList<Friends>();
	    //
	    int rows=0;
		try{
		  
	  	  FriendsDao friendsdao=new FriendsDao();
	  	  friendsdao.getConn(server, db, user, pwd);
		  //��ȡ���ResultSet
		  ResultSet rs=friendsdao.executeQuery(sql, para);
		  //��ý�������
		  while(rs.next()){
				//����Ϣ��װ��User������
				Friends friends=new Friends();
				friends.setFriend(rs.getString("friend"));
				friends.setMe(rs.getString("me"));
				friends.setMessage(rs.getString("message"));
				
				list.add(friends);
		     }
		  
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
		//System.out.println(rows);
		return list;   //return the list of the result set
	}
	public int sendMessage(String server,String db,String user,String pwd,String me,String message)
	{
		int result=-1;
		System.out.println("进入sendmessage");
		System.out.println(me);
		System.out.println(message);
		
		String sql="update friends set message=? where me=?";
		String[] params={message,me};
		System.out.println(sql);
		try{
			  
		  	  FriendsDao friendsdao=new FriendsDao();
		  	  friendsdao.getConn(server, db, user, pwd);
		  	result = friendsdao.executeUpdate(sql, params);
		  	
		  	
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
		
		return result;
	}
	
}
