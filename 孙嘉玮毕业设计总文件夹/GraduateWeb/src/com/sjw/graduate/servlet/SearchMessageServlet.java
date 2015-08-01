package com.sjw.graduate.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import com.sjw.gradute.entity.Friends;
import com.sjw.graduate.dao.FriendsDao;

public class SearchMessageServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public SearchMessageServlet() {
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
	    //
	  	ServletContext ctx=this.getServletContext();
	  	String server=ctx.getInitParameter("server");
	  	String db=ctx.getInitParameter("db");
	  	String user=ctx.getInitParameter("user");
	  	String pwd=ctx.getInitParameter("pwd");
	  	
	  	FriendsDao friendsdao=new FriendsDao();
	  	ArrayList<Friends> list=friendsdao.searchFriends(server, db, user, pwd, request.getParameter("me"));
	    
	    String message="";
	    for(int i=0;i<list.size();i++){
	      message=message+list.get(i).getMe()+"|"+list.get(i).getMessage()+"|";
	    }
	    out.print(message);
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
