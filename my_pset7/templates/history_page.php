<div>
    <!--<img alt="Under Construction" src="img/construction.gif"/>-->
    
    <?php 
		
		$history = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
		
		//print_r($history);
		
    ?>
    
    	<table  class="table table-striped">
			<thead>
				<tr>	
				<td class="table_header"> Transaction Type </td>
				<td class="table_header"> Company </td>
				<td class="table_header"> Symbol </td>
				<td class="table_header"> Shares </td>
				<td class="table_header"> Price </td>
				<td class="table_header"> Date / Time </td>
				</tr>
 			</thead>
 			<tbody>	
 			<?php foreach($history as $hist ): ?>
				<tr>
					<td> <?= $hist["transaction_type"] ?> </td>
					<td> <?= $hist["company"] ?> </td>
					<td> <?= $hist["symbol"] ?> </td>
					<td> <?= $hist["shares"] ?> </td>
					<td> <?= number_format($hist["price"],2,".",",") ?> </td>
					<td> <?= $hist["time_stamp"] ?> </td>
				</tr>	
 			<?php endforeach ?>
 			</tbody>
		</table>	
    
</div>    
