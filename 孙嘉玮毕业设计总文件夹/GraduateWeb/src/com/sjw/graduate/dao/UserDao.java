package com.sjw.graduate.dao;

import java.sql.ResultSet;
import java.util.ArrayList;




import com.sjw.gradute.entity.User;

public class UserDao extends DBOper {
	public int addUser(User user){
		String sql="INSERT INTO user(username,password)" +
				       "values(?,?)";
		String[] params={user.get_username(),user.get_passwprd()};
		int result=this.executeUpdate(sql, params);
		return result;
		}

public ArrayList<User> getUser(String server,String db,String user,String pwd){
	//��Ž��������
    ArrayList<User> list=new ArrayList<User>();
	try{
	//����UserDao��������ݿ����
  	UserDao userdao=new UserDao();
  	userdao.getConn(server, db, user, pwd);
	String sql="SELECT * FROM User";
	//��ȡ�����ResultSet
	ResultSet rs=userdao.executeQuery(sql, null);
	//���������е�����
	
	while(rs.next()){
		//����Ϣ��װ��User������
		User user1=new User();

		user1.set_username(rs.getString("username"));
		user1.set_password(rs.getString("password"));
		list.add(user1);
     }
	}catch(ClassNotFoundException e){
		e.printStackTrace();
	}catch(Exception e){
		e.printStackTrace();
	}
    return list;
    
}

public int searchDIDIUser(String server,String db,String user,String pwd,String username,String password){
	//������
	String[] para={username,password};
	System.out.println("----------------------------------");
	System.out.println("��������־��");
	System.out.println("�û�"+username+"�����¼...\n");
	//System.out.println(password);
	//��ѯ����
	String sql="SELECT * FROM user WHERE username=? and password=?";
	//��Ž��������
    ArrayList<User> list=new ArrayList<User>();
    //��ѯ�������
    int rows=0;
	try{
	  //����UserDao��������ݿ����
  	  UserDao userdao=new UserDao();
  	  userdao.getConn(server, db, user, pwd);
	  //��ȡ�����ResultSet
	  ResultSet rs=userdao.executeQuery(sql, para);
	  //��ý��������
	  rs.last();
	  rows = rs.getRow();
	}catch(ClassNotFoundException e){
		e.printStackTrace();
	}catch(Exception e){
		e.printStackTrace();
	}
	//System.out.println(rows);
	return rows;
}





}