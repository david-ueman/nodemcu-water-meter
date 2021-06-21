<?php
	//Example of expected request:
	//http://url_to_your_site.net/store_data_reading.php?water_volume=10&tank_id=0

	echo "Hi! this is $_SERVER[REMOTE_ADDR]...<br><br>" . PHP_EOL;

	$value = $_GET['water_volume'];
	$id = $_GET['tank_id'];
	
	echo "The water volume in tank $_GET[tank_id] is $_GET[water_volume]" . PHP_EOL;
	
	ini_set('display_errors', 1);
	ini_set('display_startup_errors', 1);
	error_reporting(E_ALL);

	require 'database_link.php';

	echo "Trying to open a connection to the database...";	
	if (!$link) {
		echo "Error: Unable to connect to MySQL." . PHP_EOL;
		echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
		echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
		exit;
	}
	else
	{
		echo "Connected..." . PHP_EOL;
		
		//Forcing to cast each value to a numeric type
		//so that we can erase the leading zeros or
		//any other character that prevents the database
		//to understand the values as numeric values
		foreach ($_GET as &$value) {
			$value = str_replace ("'", "", $value);
			$value = floatval ($value);
		}
		
		$sqlInsertQuery = "INSERT INTO `eslaekomedidas`.`aguaparaeleko_data` (
				`volume`, 
				`tank_id`
			)
			VALUES (" . 
				$_GET['water_volume'] . "," .
				$_GET['tank_id'] . ");";
	
		if (mysqli_query($link, $sqlInsertQuery))
		{
			echo "The query was executed successfully!" . PHP_EOL;
		} else {
			echo "The query resulted in ERROR :(," . PHP_EOL;
			echo "full SQL query: $sqlInsertQuery" . PHP_EOL;
			echo mysqli_error($link) . PHP_EOL;
		}

		echo "Closing connection to database..." . PHP_EOL;
		mysqli_close($link);
	}

?>
