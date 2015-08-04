package com.sjw.graduate.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sjw.graduate.dao.FriendsDao;
import com.sjw.gradute.entity.Friends;

public class AddFriendsServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public AddFriendsServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html; charset=UTF-8" );
		PrintWriter out = response.getWriter();
		//�������л�ȡ�ͻ����ύ����Ϣ
		String me=request.getParameter("me");
		String friend=request.getParameter("friend");
		
		//�������Ϣ��װ��DIDIUser������
		Friends friends=new Friends();
		friends.setMe(me);
		friends.setFriend(friend);
		//��ȡ������ݿ�ĳ�ʼ������
		ServletContext ctx=this.getServletContext();
		String server=ctx.getInitParameter("server");
		String db=ctx.getInitParameter("db");
		String user=ctx.getInitParameter("user");
		String pwd=ctx.getInitParameter("pwd");
		//����UserDao�������ݿ����
		FriendsDao friendsdao=new FriendsDao();
		try{
			friendsdao.getConn(server, db, user, pwd);
			if(friendsdao.addUser(friends)==1){
				out.print("1");
			}
			else{
				out.print("0");
			}
//			out.print("����");
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
