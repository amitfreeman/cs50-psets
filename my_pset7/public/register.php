<?php

    //configuration
    require("../includes/config.php");

    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //TODO
        
        if( empty($_POST["username"]) )
        {
            apologize("You must provide a username");
        }
        else if( empty($_POST["password"]) || empty($_POST["confirmation"]) )
        {
            apologize("You must fill both password fields");
        }
        else if( $_POST["password"] !== $_POST["confirmation"] )
        {
            apologize("Sorry, passwords entered do not match");
        }
        else if( !preg_match("/([\w\-]+\@[\w\-]+\.[\w\-]+)/",$_POST["email"]) )
        {
				apologize("Sorry, invalid email address");
		}
        
        $Q = query("INSERT INTO users (username,hash,cash,email) VALUES(?,?,10000.0000,?)", $_POST["username"],crypt($_POST["password"]), $_POST["email"]);
        
        if( $Q === false)
        {
            apologize("Sorry , Insert failed");
        }
        
        $rows = query("SELECT LAST_INSERT_ID() as id");
        //dump($rows);
        
        $_SESSION["id"] = $rows[0]["id"];
        redirect("/");
    }
    else
    {   
        //else render form
        render("register_form.php",["title" => "Register"]);
    }
?>
