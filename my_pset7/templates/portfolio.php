<div>
    <!--<img alt="Under Construction" src="img/construction.gif"/>-->
    <?php if (isset($stocks)): ?>
		<table  class="table table-striped">
			<thead>
				<tr>	
				<td class="table_header"> Symbol </td>
				<td class="table_header"> Name </td>
				<td class="table_header"> Price </td>
				<td class="table_header"> Shares </td>
				<td class="table_header"> Total Value </td>
				</tr>
 			</thead>
 			<tbody>	
 			<?php foreach($stocks as $stock ): ?>
				<tr>
					<td> <?= $stock["symbol"] ?> </td>
					<td> <?= $stock["name"] ?> </td>
					<td> <?= number_format($stock["price"],2,".",",") ?> </td>
					<td> <?= $stock["shares"] ?> </td>
					<td> <?= number_format($stock["shares"] * $stock["price"],2,".",",") ?> </td>
				</tr>	
 			<?php endforeach ?>
				<tr>
					<td class="user_cash"> Your Cash </td>
					<td></td>
					<td></td>
					<td></td>
					<td class="user_cash"> <?= number_format($cash,2,".",",") ?> </td>
				</tr>
 			</tbody>
		</table>	
    <?php endif ?>
</div>
<!-- (put it in header)<div>
    <a href="logout.php">Log Out</a>
</div>-->
