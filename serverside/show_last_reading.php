<?php
	ini_set('display_errors', 1);
	ini_set('display_startup_errors', 1);
	error_reporting(E_ALL);

    require 'database_link.php';

	if (!$link) {
		echo "Error: Unable to connect to MySQL." . PHP_EOL;
		echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
		echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
		exit;
	}
	else
	{
		if (isset($_GET) && isset($_GET['tank_id']))
		{
			$tank_id = $_GET['tank_id'];
		}
		else
		{
			$tank_id = 1;
		}

		$sqlQuery = "SELECT * FROM `aguaparaeleko_data` WHERE 1 AND tank_id = $tank_id ORDER BY id DESC LIMIT 1;";
	
		if ($sqlResult = mysqli_query($link, $sqlQuery))
		{
			if ($sqlResult->num_rows > 0){
				$data_array = $sqlResult->fetch_array();
				
				echo	"Agua en Depositos: $data_array[volume] L <br> 
						Última lectura: $data_array[date]";
			} else {
				echo "The query didn't throw any row with data!" . PHP_EOL;
			}	
		} else {
			echo "The query resulted in ERROR :(," . PHP_EOL;
			echo "full SQL query: $sqlQuery" . PHP_EOL;
			echo mysqli_error($link) . PHP_EOL;
		} 
		mysqli_close($link);
	}

?>
