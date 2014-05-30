<!-- //Its to reset password after logged in -->
<form action="reset_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="old_password" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">
            <input autofocus class="form-control" name="new_password1" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input autofocus class="form-control" name="new_password2" placeholder="Re-enter new Password" type="password"/>
        </div>

        <div class="form-group">
            <button type="submit" class="btn btn-default">Reset</button>
        </div>
    </fieldset>
</form>
