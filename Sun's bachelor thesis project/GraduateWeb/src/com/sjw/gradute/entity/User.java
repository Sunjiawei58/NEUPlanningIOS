package com.sjw.gradute.entity;

public class User {
	private int id;
	private String username;
	private String password;
	
	public User(){}
	public int get_id()
	{return id;}
	public void set_id(int id)
	{this.id = id;}
	
	public String get_username()
	{return username;}
	public void set_username(String username)
	{this.username= username;};
	public String get_passwprd()
	{return password;}
	public void set_password(String password)
	{this.password=password;}
}
