package com.sjw.graduate.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sjw.gradute.entity.Message;
import com.sjw.graduate.dao.MessageDao;


public class AddMessageServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public AddMessageServlet() {
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

		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html; charset=UTF-8" );
		PrintWriter out = response.getWriter();
		//从请求中获取客户端提交的信息
		String sendUser=request.getParameter("sendUser");
		String getUser=request.getParameter("getUser");
		String message = request.getParameter("message");
		//将获得信息封装到DIDIUser对象中
		Message mess=new Message();
		
		mess.setSendUser(sendUser);
		mess.setGetUser(getUser);
		mess.setMessage(message);
		
		//获取连接数据库的初始化参数
		ServletContext ctx=this.getServletContext();
		String server=ctx.getInitParameter("server");
		String db=ctx.getInitParameter("db");
		String user=ctx.getInitParameter("user");
		String pwd=ctx.getInitParameter("pwd");
		//调用UserDao，完成数据库操作
		MessageDao messagedao=new MessageDao();
		try{
			messagedao.getConn(server, db, user, pwd);
			if((messagedao.addMessage(mess))==1){
				out.print("添加信息成功！");
			}
			else{
				out.print("添加信息失败！");
			}
			out.print("返回");
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
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
