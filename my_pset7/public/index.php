<?php

    // configuration
    require("../includes/config.php"); 
    
    //printf($_SERVER["PHP_SELF"]);
	
	/* Query users portfolio */
	
	$rows = query('SELECT symbol, shares FROM portfolio WHERE id = ?', $_SESSION["id"]);
	
	//dump($rows);
	
	$stocks = array();
    foreach( $rows as $row )
	{		
			$stock  = lookup($row["symbol"]);
			if($stock !== false)
			{
				$stocks[] = [ "symbol" => $stock["symbol"],
							  "name" => $stock["name"],
							  "price" => $stock["price"],
							   "shares" => $row["shares"]];
		    }		
	}
	
	//dump($stocks);
	
	$cash_arr = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
	
	$cash = 0;
	foreach($cash_arr as $cash)
	{
		$cash = $cash["cash"];
	}
			
    //render portfolio
    render("portfolio.php", ["title" => "Portfolio", "stocks" => $stocks, "cash" => $cash]);

?>
