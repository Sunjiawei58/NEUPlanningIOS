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
		//��Ž��������
	    ArrayList<Message> list=new ArrayList<Message>();
		try{
		//����UserDao��������ݿ����
	  	MessageDao messagedao=new MessageDao();
	  	messagedao.getConn(server, db, user, pwd);
		String sql="SELECT * FROM Message";
		//��ȡ�����ResultSet
		ResultSet rs=messagedao.executeQuery(sql, null);
		//���������е�����
		
		while(rs.next()){
			//����Ϣ��װ��User������
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
		//������
		String[] para={getUser};
		System.out.println("----------------------------------");
		System.out.println("��������־��");
		System.out.println("�û�"+getUser+"�����¼...\n");
		//System.out.println(password);
		//��ѯ����
		String sql="SELECT * FROM message WHERE getUser=?";
		//��Ž��������
	    ArrayList<Message> list=new ArrayList<Message>();
	    //��ѯ�������
	    int rows=0;
		try{
		  //����UserDao��������ݿ����
	  	  MessageDao messagedao=new MessageDao();
	  	  messagedao.getConn(server, db, user, pwd);
		  //��ȡ�����ResultSet
		  ResultSet rs=messagedao.executeQuery(sql, para);
		  //��ý��������
		  while(rs.next()){
				//����Ϣ��װ��User������
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
