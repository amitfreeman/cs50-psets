<!DOCTYPE html>

<html>

    <head>

        <link href="css/bootstrap.min.css" rel="stylesheet"/>
        <link href="css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="js/jquery-1.10.2.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <script src="js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="img/logo.gif"/></a>
            </div>
            <br>
            <div id="bar">
		<?php if (isset($_SESSION["id"])): ?>
		<span> <a href="index.php">Home</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="quote.php">Quote</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="buy.php">Buy</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="sell.php">Sell</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="history.php">History</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="reset_password.php">Reset Password</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <span> <a href="logout.php">Log out</a> </span> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <?php endif ?>
            </div>
            <br>
            <div id="middle">
