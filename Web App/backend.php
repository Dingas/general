<!-- backend.php -->

<?php
// Oracle database connection details
$oracle_username = "d2eliopo";
$oracle_password = "04183485";
$oracle_hostname = "oracle.scs.ryerson.ca";
$oracle_port = 1521;
$oracle_sid = "orcl";

// Function to establish Oracle database connection
function connect_to_oracle() {
    $dsn = "(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=" . $GLOBALS['oracle_hostname'] . ")(PORT=" . $GLOBALS['oracle_port'] . ")))
            (CONNECT_DATA=(SERVICE_NAME=" . $GLOBALS['oracle_sid'] . ")))";
    $conn = oci_connect($GLOBALS['oracle_username'], $GLOBALS['oracle_password'], $dsn);
    return $conn;
}

// Function to execute SQL queries
function execute_query($query) {
    $conn = connect_to_oracle();
    $stid = oci_parse($conn, $query);
    oci_execute($stid);
    oci_free_statement($stid);
    oci_close($conn);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $action = $_POST["action"];
    
    // Handle the action (perform database operations) based on $action
    // Insert your PHP code for database operations here

    switch ($action) {
        case "create_tables":
            $query = "
                -- Your create tables SQL statements here
            ";
            execute_query($query);
            break;
        
        case "drop_tables":
            $query = "
                -- Your drop tables SQL statements here
            ";
            execute_query($query);
            break;

        case "populate_tables":
            $query = "
                -- Your populate tables SQL statements here
            ";
            execute_query($query);
            break;

        case "query_tables":
            $query = "
                -- Your select query here
            ";
            // Execute the query and handle the results
            // ...

            break;

        default:
            echo "Invalid action";
            break;
    }
}
?>
