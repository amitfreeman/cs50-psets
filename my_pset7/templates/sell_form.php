<form action="sell.php" method="POST">
	
	<fieldset>
			<?php if( isset($names)): ?>
				<?php foreach($names as $name): ?>
				 <div class="form-group">	
					<input class="form-control" name="stock_sell" placeholder="Sell" type="radio" value=<?=$name["name"] ?> /> <?= $name["name"] ?>
					</div>	
				<?php endforeach ?>
			<?php endif ?>
				
	   <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>	
		
	</fieldset>	
	
</form>
