<?php
	
	//its to reset password after logged in
 
    //configuration
    require("../includes/config.php");
    
	if( $_SERVER["REQUEST_METHOD"] == "POST" )
	{
		printf($_SESSION["id"]);
		
		$rows = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
		
		//print_r($rows);
		
		if(crypt($_POST["old_password"], $rows[0]["hash"]) == $rows[0]["hash"])
		 {
				if($_POST["new_password1"] == $_POST["new_password2"])
				{
					query("UPDATE users SET hash = ? WHERE id = ?",crypt($_POST["new_password1"]),$_SESSION["id"]);
				}
				else
				{
					apologize("Passwords entered do not match");
			    }	
		 }
		 else
		 {
			 apologize("Old password is wrong");
		 }
		 
		 redirect("index.php");
	}
	else
	{
			render("reset_password_form.php", ["title" => "ResetPassword"]);
	}
 
?>

