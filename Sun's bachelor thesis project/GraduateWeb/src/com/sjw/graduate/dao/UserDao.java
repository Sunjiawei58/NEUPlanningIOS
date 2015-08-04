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
	//存放结果的数组
    ArrayList<User> list=new ArrayList<User>();
	try{
	//调用UserDao，完成数据库操作
  	UserDao userdao=new UserDao();
  	userdao.getConn(server, db, user, pwd);
	String sql="SELECT * FROM User";
	//获取结果集ResultSet
	ResultSet rs=userdao.executeQuery(sql, null);
	//保存结果集中的内容
	
	while(rs.next()){
		//将信息封装到User对象中
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
	//参数表
	String[] para={username,password};
	System.out.println("----------------------------------");
	System.out.println("服务器日志：");
	System.out.println("用户"+username+"请求登录...\n");
	//System.out.println(password);
	//查询条件
	String sql="SELECT * FROM user WHERE username=? and password=?";
	//存放结果的数组
    ArrayList<User> list=new ArrayList<User>();
    //查询结果条数
    int rows=0;
	try{
	  //调用UserDao，完成数据库操作
  	  UserDao userdao=new UserDao();
  	  userdao.getConn(server, db, user, pwd);
	  //获取结果集ResultSet
	  ResultSet rs=userdao.executeQuery(sql, para);
	  //获得结果的条数
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