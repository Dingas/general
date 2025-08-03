<!-- index.php -->

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Oracle Database Interface</title>
</head>
<body>
    <h1>Oracle Database Interface</h1>
    
    <form action="backend.php" method="post">
        <button type="submit" name="action" value="create_tables">Create Tables</button>
    </form>

    <form action="backend.php" method="post">
        <button type="submit" name="action" value="drop_tables">Drop Tables</button>
    </form>

    <form action="backend.php" method="post">
        <button type="submit" name="action" value="populate_tables">Populate Tables</button>
    </form>

    <form action="backend.php" method="post">
        <button type="submit" name="action" value="query_tables">Query Tables</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $action = $_POST["action"];
        
        // Handle the action (perform database operations) based on $action
        // Insert your PHP code for database operations here
        echo "<p>Action: $action</p>";
    }
    ?>
</body>
</html>
