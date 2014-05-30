<form action = "quote.php" method = "post">
    
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="quote" placeholder="Stock Symbol" type="text" />
        </div>
         <div class="form-group">
            <button type="submit" class="btn btn-default">Get Quote</button>
        </div>
    </fieldset>

</form>
<br>
 <div class="price_display">
<?php if (isset($price)): ?>
        <span style="font-size: 20px;font-family: futura,sans-serif;"> Price of  <?= $price["name"] ?> is $<?= number_format($price["price"],2); ?> </span>
<?php endif ?>   
 </div> 
<br>
<!-- (put it in header)<div>
    or <a href="index.php">Home</a> 
</div>-->

