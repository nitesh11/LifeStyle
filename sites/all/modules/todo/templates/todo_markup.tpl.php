<?php
	foreach ($todos as $key => $todo) {
		print '<input type = "checkbox" value="' . $todo . '" >' . $todo;
	}
?>