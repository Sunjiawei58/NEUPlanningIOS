package com.sjw.graduate.dao;

import java.sql.ResultSet;
import java.util.ArrayList;


import com.sjw.gradute.entity.Message;

public class MessageDao extends DBOper {

	
	public int addMessage(Message message){
		String sql="INSERT INTO Message(sendUser,getUser,message)" +
				       "values(?,?,?)";
		String[] params={message.getSendUser(),message.getGetUser(),message.getMessage()};
		int result=this.executeUpdate(sql, params);
		return result;
		}
	
	public ArrayList<Message> getMessage(String server,String db,String user,String pwd){
		//存放结果的数组
	    ArrayList<Message> list=new ArrayList<Message>();
		try{
		//调用UserDao，完成数据库操作
	  	MessageDao messagedao=new MessageDao();
	  	messagedao.getConn(server, db, user, pwd);
		String sql="SELECT * FROM Message";
		//获取结果集ResultSet
		ResultSet rs=messagedao.executeQuery(sql, null);
		//保存结果集中的内容
		
		while(rs.next()){
			//将信息封装到User对象中
			Message message=new Message();
			
			message.setSendUser(rs.getString("sendUser"));
			message.setGetUser(rs.getString("getUser"));
			message.setMessage(rs.getString("message"));
			list.add(message);
	     }
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
	    return list;
	    
	}
	
	public ArrayList<Message> searchMessage(String server,String db,String user,String pwd,String getUser){
		//参数表
		String[] para={getUser};
		System.out.println("----------------------------------");
		System.out.println("服务器日志：");
		System.out.println("用户"+getUser+"请求登录...\n");
		//System.out.println(password);
		//查询条件
		String sql="SELECT * FROM message WHERE getUser=?";
		//存放结果的数组
	    ArrayList<Message> list=new ArrayList<Message>();
	    //查询结果条数
	    int rows=0;
		try{
		  //调用UserDao，完成数据库操作
	  	  MessageDao messagedao=new MessageDao();
	  	  messagedao.getConn(server, db, user, pwd);
		  //获取结果集ResultSet
		  ResultSet rs=messagedao.executeQuery(sql, para);
		  //获得结果的条数
		  while(rs.next()){
				//将信息封装到User对象中
				Message message=new Message();
				
				message.setSendUser(rs.getString("sendUser"));
				message.setGetUser(rs.getString("getUser"));
				message.setMessage(rs.getString("message"));
				list.add(message);
		     }
		  
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
		//System.out.println(rows);
		return list;   //return the list of the result set
	}
	
	
	
}
