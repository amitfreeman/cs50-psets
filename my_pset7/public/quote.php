<?php
    
    //configuration
    require("../includes/config.php");
    
    if( $_SERVER["REQUEST_METHOD"] == "POST" )
    {
        $quote_info = lookup($_POST["quote"]);
        
        //dump($quote_price);
        
         if($quote_info === false)
         {
            apologize("Can't find symbol");
         }
         else
         {
            render("quote_form.php",["title" => "Stock check" , "price" => $quote_info]);
         }
    }
    else
    {
        //else render form
        render("quote_form.php",["title" => "Stock check" ]);
    }
?>
