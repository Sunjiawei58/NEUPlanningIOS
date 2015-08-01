package com.sjw.graduate.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sjw.gradute.entity.Friends;
import com.sjw.graduate.dao.FriendsDao;

public class SendMessageServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public SendMessageServlet() {
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

		response.setContentType("text/html; charset=UTF-8" );
	    PrintWriter out = response.getWriter();
	    //格式
	  	ServletContext ctx=this.getServletContext();
	  	String server=ctx.getInitParameter("server");
	  	String db=ctx.getInitParameter("db");
	  	String user=ctx.getInitParameter("user");
	  	String pwd=ctx.getInitParameter("pwd");
	  	int num=-1;
	  	//链接数据库
	  	FriendsDao friendsdao=new FriendsDao();
	  	System.out.println(num);
//	  	try{
		//	userdao.getConn(server, db, user, pwd);
	  	String me = request.getParameter("me");
	  	String message=request.getParameter("message");
	  	me = new String(me.getBytes("ISO8859-1"),"UTF-8");
	  	message = new String(message.getBytes("ISO8859-1"),"UTF-8");
		num=friendsdao.sendMessage(server, db, user, pwd, me, message);
		System.out.println(num);
//		}catch(ClassNotFoundException e){
//			e.printStackTrace();
//		}catch(Exception e){
//			e.printStackTrace();
//		}
	    
	    //String message="";
	    //ArrayList<String> list=db.getList();
	    //for(int i=0;i<list.size();i++){
	    //  message=message+list.get(i)+"\r\n";
	    //}
	    //out.print(message);
		//out.print("��¼�ɹ�");
	  	String s= Integer.toString(num);
	  	out.print(s);
	    out.flush();
	    out.close();
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
