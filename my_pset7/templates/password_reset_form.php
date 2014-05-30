<!-- //Its to send password over mail after forgotten -->
<form action="password_reset.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="username" placeholder="Username" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="email" placeholder="Email" type="text" />
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Reset</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="login.php">log in</a> 
</div>
