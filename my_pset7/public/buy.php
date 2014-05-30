<?php

	//configurations
	require("../includes/config.php");

	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
			$quote_info = lookup($_POST["symbol"]);
			$shares = $_POST["shares"];
        
            if( $quote_info === false )
            {
				apologize("Could not find symbol");
			}
            else if (preg_match("/^\d+$/", $shares) == false)
            {
              	apologize("Number of shares shoud be positive integer");
		    }
		    else
		    {
				$cash_r = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
				
				//printf($cash_r[0]["cash"]);
				//printf($cash_r[0]["cash"]." ".$quote_info["price"]." ".$shares." ".$shares * $quote_info["price"]);
				
				$cost = $shares * $quote_info["price"];
				
				if( $cash_r[0]["cash"] < $cost)
				{
						apologize("Insufficient funds, You are short by $".number_format($cost - $cash_r[0]["cash"],2,".",","));
				}
				else
				{
					//deduct the cost from cash of user
					query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
					
					//add stocks to users portfolio
					query("INSERT INTO portfolio (id, symbol, shares) VALUES(?,?,?) ON DUPLICATE KEY UPDATE shares = shares + ?",$_SESSION["id"],$quote_info["symbol"],$shares,$shares);
					
					query("INSERT INTO history (id,transaction_type,company,symbol,shares,price) VALUES(?,\"BUY\",?,?,?,?)",$_SESSION["id"],$quote_info["name"],$quote_info["symbol"],$shares,$quote_info["price"]);
					
					redirect("index.php");
				}
			}
	}
	else
	{
		
			render("buy_form.php", ["title" => "buy"]);
	}
			
	
?>
