package com.sjw.graduate.dao;
import java.awt.List;
import java.sql.*;
import java.util.ArrayList;

public class DBOper {
	Connection conn=null;
	PreparedStatement pstmt=null;
	ResultSet rs=null;
	
	public Connection getConn(String server,String db,String user,String pwd)
		throws ClassNotFoundException,InstantiationException,
		IllegalAccessException,SQLException{
		//JDBC��
		String driver="com.mysql.jdbc.Driver";
		//�����ַ�
		String url="jdbc:mysql://"+server+":3306/"+db+"?user="+user
				+"&password="+pwd+"&useUnicode=true&characterEncoding=UTF-8";
		//����JDBC��
		Class.forName(driver).newInstance();
		//��ȡ����
		conn=DriverManager.getConnection(url);
		//��������
		return conn;
	}
	
	public ResultSet executeQuery(String sql,String[] params){
		try{
			//��ȡPreparedStatement����
			pstmt=conn.prepareStatement(sql);
			//����PreparedStatement����Ĳ���
			if(params!=null){
				for(int i=0;i<params.length;i++){
					pstmt.setString(i+1, params[i]);
				}
			}
			//ִ�в�ѯ�����ؽ��
			rs=pstmt.executeQuery();
		}catch(SQLException e){
			e.printStackTrace();
		}
		return rs;
	}
	
	public int executeUpdate(String sql,String[] params){
		int n=0;
		try{
			System.out.println("executeUpdate........");
			//��ȡPreparedStatement����
			pstmt=conn.prepareStatement(sql);
			//����PreparedStatement����Ĳ���
			if(params!=null){
				System.out.println("pstmt is right:");
				System.out.println(params.length);
				for(int i=0;i<params.length;i++){
					pstmt.setString(i+1, params[i]);
				}
			}
			//ִ�и��£�������Ӱ��ļ�¼
			n=pstmt.executeUpdate();
		}catch(SQLException e){
			e.printStackTrace();
		}
		return n;
	}
	
	public void closeAll(){
		//�ر�ResultSet
		if(rs!=null){
			try{
				rs.close();
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
		//�ر�PreparedStatement
		if(pstmt!=null){
			try{
				pstmt.close();
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
		//�ر�Connection
		if(conn!=null){
			try{
				conn.close();
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
	}
	
/*
String userName="root";
String password="cxfpc12358";
Connection conn=null;
Statement stmt=null;

String  url="jdbc:mysql://localhost:3306/didixc";

ArrayList<String> list=new ArrayList<String>();
String sql;
public DBOper(){
  sql="select * from didixc;";
  try {
  Class.forName("com.mysql.jdbc.Driver");
  System.out.println("����سɹ�...!");
  conn=DriverManager.getConnection(url,userName,password);
  System.out.println("������ݿ�ɹ�...!");
  stmt=conn.createStatement();
  ResultSet rst=stmt.executeQuery(sql);
  while(rst.next()){
    //String name=new   String(rst.getString("name").getBytes("latin1"), "UTF-8"); www.it165.net
    String name=new   String(rst.getString("name").getBytes("latin1"), "GB2312");// ����Ҫ�ɲ�Ҫ�����㲻��������Ϊ׼
    //Ҳ�ɲ���ת����ֱ��д��String name=rst.getString("name");
    list.add(name);
  }
  rst.close();
  }catch (Exception e){
  //TODO Auto-generated catch block
    e.printStackTrace();
  }
}

public ArrayList<String> getList(){
    return list;
  }
  */
}