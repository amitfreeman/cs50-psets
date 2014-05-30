<?php
	//configurations
	require("../includes/config.php");
	
	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
			$results = query("SELECT shares FROM portfolio WHERE id=? AND symbol=?",$_SESSION["id"], $_POST["stock_sell"]);
			
			$no_shares = 0;
			
			foreach( $results as $result )
			{
					$no_shares = $result["shares"];
		    }
		   
			
			$stock_info = lookup($_POST["stock_sell"]);
	
			$sell_value = $stock_info["price"] * $no_shares;
			
			query("UPDATE users SET cash = cash + ? WHERE id = ?", $sell_value, $_SESSION["id"]);
			
			query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["stock_sell"]);
			
			query("INSERT INTO history (id,transaction_type,company,symbol,shares,price) VALUES(?,\"SELL\",?,?,?,?)",$_SESSION["id"],$stock_info["name"],$stock_info["symbol"],$no_shares,$stock_info["price"]);
			
			redirect("index.php");
    }
    else
    {
		$rows = query('SELECT symbol, shares FROM portfolio WHERE id = ?', $_SESSION["id"]);
		
		if($rows !== false)
		{
			$stock_names = array();
			foreach($rows as $row)
			{
					
					$stock_names[] = ["name" => $row["symbol"]];
			}
			
			render("sell_form.php", ["title" => "Sell", "names" => $stock_names]);
	   }
	   else
	       render("sell_form.php", ["title" => "Sell"]);
    }
	
?>
