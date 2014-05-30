<?php
	//Its to send password over mail after forgotten
	
     //configuration
    require("../includes/config.php");
     //echo $_SERVER["PHP_SELF"];
		if($_SERVER["REQUEST_METHOD"] == "POST")
		{
			$results = query("SELECT username,email FROM users WHERE username = ?",$_POST["username"]);
			
			//print_r($results);
			if($results != false)
			{
					if($results[0]["email"] == $_POST["email"])
					{
							require_once("PHPMailer/class.phpmailer.php");

							// instantiate mailer
							$mail = new PHPMailer();
							
							$mail->IsSMTP();
							$mail->Host = "smtp.comcast.net";
							
							
							// set From:
							//$mail->SetFrom("finance");

							// set To:
							$mail->AddAddress($_POST["email"]);
							
							$mail->Subject = "Password Reset for your account";
							
							$mail->Body = "Password for your account at finance is - test";
							
							// send mail
							if ($mail->Send() === false)
								die($mail->ErrorInfo . "\n");
					}
					else
					{
						apologize("email entered do not match with registered email");
					}
			}
			else
			{
				apologize("records can't be found, enter username again");
			}
			 
		}
		else{
		//else render form		
            render("password_reset_form.php", ["title" => "Password Reset"]);
	    }
	 
	
?>
