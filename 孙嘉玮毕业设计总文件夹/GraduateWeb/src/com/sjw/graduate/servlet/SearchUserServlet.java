package com.sjw.graduate.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sjw.gradute.entity.User;
import com.sjw.graduate.dao.UserDao;

public class SearchUserServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public SearchUserServlet() {
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

		response.setContentType("text/html; charset=UTF-8" );
	    PrintWriter out = response.getWriter();
	    //获取连接数据库的初始化参数
	  	ServletContext ctx=this.getServletContext();
	  	String server=ctx.getInitParameter("server");
	  	String db=ctx.getInitParameter("db");
	  	String user=ctx.getInitParameter("user");
	  	String pwd=ctx.getInitParameter("pwd");
	  	int num=-1;
	  	//调用UserDao，完成数据库操作
	  	UserDao userdao=new UserDao();
	  	//try{
		//	userdao.getConn(server, db, user, pwd);
		num=userdao.searchDIDIUser(server, db, user, pwd, request.getParameter("name"), request.getParameter("password"));
			
		//}catch(ClassNotFoundException e){
		//	e.printStackTrace();
		//}catch(Exception e){
		//	e.printStackTrace();
		//}
	    
	    //String message="";
	    //ArrayList<String> list=db.getList();
	    //for(int i=0;i<list.size();i++){
	    //  message=message+list.get(i)+"\r\n";
	    //}
	    //out.print(message);
		//out.print("登录成功");
	  	String s= Integer.toString(num);
	  	out.print(s);
	    out.flush();
	    out.close();
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

		doGet(request, response);
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
