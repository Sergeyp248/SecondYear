var array = [
	{
		"name": "iPhone X",
		"price": 450,
		"quality": 6,
		"id": 431,
	},
	{
		"name": "Samsung S9",
		"price": 250,
		"quality": 9,
		"id": 123,
	},
	{
		"name": "Huawei P20",
		"price": 340,
		"quality": 4,
		"id": 982
	},
	{
		"name": "iPhone 5S",
		"price": 230,
		"quality": 8,
		"id": 901
	},
	{
		"name": "Xiaomi 5A",
		"price": 140,
		"quality": 3,
		"id": 732
	}
];

window.onload = function() {

	var d = document;

	var returnBackButton = d.getElementById("returnBack"),
		idField = d.getElementById("idField"),
		nameField = d.getElementById("nameField"),
		priceField = d.getElementById("priceField"),
		qualityField = d.getElementById("qualityField"),
		submitButton = d.getElementById("submit");

	var button1 = d.getElementById("button1"),
		button2 = d.getElementById("button2"),
		button3 = d.getElementById("button3");

	button1.addEventListener("click", handler1);
	button2.addEventListener("click", handler2);
	button3.addEventListener("click", handler3);
	returnBackButton.addEventListener("click", handler);
	submitButton.addEventListener("click", submitHandler);

	var sortedArray = new Array(array.length);

	for(var i = 0; i < sortedArray.length; i++) {
		var clone = {};
		cloneObject(array[i], clone);
		sortedArray[i] = clone;
	}

	function cloneObject(obj, clone) {
		for(key in obj) {
			clone[key] = obj[key];
		}
	}

	hideForm();	

	hideReturnBackButton()

	function createTable(cols, rows) {

		var oldTable = d.getElementsByTagName("table")[0];

		if(oldTable !== undefined) {
			oldTable.remove();
		}
	
		var table = d.createElement("table");
		var tr = d.createElement("tr");
		for(var i = 0; i < cols; i++) {
			var th = d.createElement("th");
			var a = d.createElement("a");
				th.appendChild(a);
				tr.appendChild(th); 
		}
		table.appendChild(tr);
		for(var i = 0; i < rows; i++) {
			tr = d.createElement("tr");
			for(var j = 0; j < cols; j++) {
				var td = d.createElement("td");
				tr.appendChild(td);
			}
			table.appendChild(tr);
		}
		d.body.appendChild(table);

		return table;
	}

	function fillingTable(newTable, arr, cols, rows) {
		for(var i = 0; i < rows + 1; i++) {

			var tr = newTable.getElementsByTagName("tr")[i];
			var counter = 0;

			if(i == 0) {
				for(var key in arr[i]) {
					var a = tr.getElementsByTagName("th")[counter++].getElementsByTagName("a")[0];
					a.innerHTML = key;
					a.setAttribute('id', key);
					if(counter >= cols) { break; }
				}
				continue;
			}

			counter = 0;

			for(var key in arr[i - 1]) {
				tr.getElementsByTagName("td")[counter++].innerHTML = arr[i - 1][key];
				if(counter >= cols) { break; } 
			}
		}
	}

	function handler1() {

		hideButtons();
		showReturnBackButton();
		hideInputFields();
		showForm();
	
		var rows = sortedArray.length,
			cols = 2;

		var newTable = createTable(cols, rows); 
		
		fillingTable(newTable, sortedArray, cols, rows);

		addListenersToColsButtons(cols, rows);
		
	}

	function handler2() {

		hideButtons();
		showReturnBackButton();
		hideInputFields();
		showForm();
	
		var rows = sortedArray.length,
			cols = 3;

		var newTable = createTable(cols, rows); 
		
		fillingTable(newTable, sortedArray, cols, rows);

		addListenersToColsButtons(cols, rows);
		
	}

	function handler3() {

		hideButtons();
		showReturnBackButton();
		showForm();

		var rows = sortedArray.length,
			cols = 4;

		var newTable = createTable(cols, rows); 
		
		fillingTable(newTable, sortedArray, cols ,rows);

		addListenersToColsButtons(cols, rows);
			
	}

	function handler() {
		hideReturnBackButton()
		var table = d.getElementsByTagName("table")[0];
		table.remove();
		showButtons();
		showInputFields();
		hideForm();
	}

	function submitHandler() {
		var newObject = {"name": null, "price": null, "quality": null, "id": null};

		newObject.name = nameField.value; 
		newObject.price = Number(priceField.value);
		newObject.quality = Number(qualityField.value);
		newObject.id = Number(idField.value);

		nameField.value = "";
		priceField.value = "";
		qualityField.value = "";
		idField.value = "";

		if(qualityField.style.display == "none" && idField.style.display == "none") {
			if(newObject.name == "" || newObject.price == 0) {
				alert("All fields must be filled!");
			}
			else {
				sortedArray.push(newObject);
				handler1();
			}

			return;
		}

		if(qualityField.style.display != "none" && idField.style.display == "none") {
			if(newObject.name == "" || newObject.price == 0 || newObject.quality == 0) {
				alert("All fields must be filled!");
			}
			else {
				sortedArray.push(newObject);
				handler2();
			}
			return;
		}

		if(qualityField.style.display != "none" && idField.style.display != "none") {
			if(newObject.name == "" || newObject.price == 0 || newObject.quality == 0 || newObject.id == 0) {
				alert("All fields must be filled!");
			}
			else {
				sortedArray.push(newObject);
				handler3();
			}

			return;
		}

		return;
	}

	function sortNameHandler(cols, rows) {
		sortedArray.sort(compareName);
		var newTable = createTable(cols, rows);
		fillingTable(newTable, sortedArray, cols, rows);
		addListenersToColsButtons(cols, rows);

		function compareName(goodA, goodB) {
  			return goodA.name.toLowerCase() > goodB.name.toLowerCase();
		}
	}

	function sortPriceHandler(cols, rows) {
		sortedArray.sort(comparePrice);
		var newTable = createTable(cols, rows);
		fillingTable(newTable, sortedArray, cols, rows);
		addListenersToColsButtons(cols, rows);

		function comparePrice(goodA, goodB) {
			return goodA.price - goodB.price;
		}
	}

	function sortQualityHandler(cols, rows) {
		sortedArray.sort(compareQuality);
		var newTable = createTable(cols, rows);
		fillingTable(newTable, sortedArray, cols, rows);
		addListenersToColsButtons(cols, rows);

		function compareQuality(goodA, goodB) {
			return goodA.quality - goodB.quality;
		}
	}

	function sortIdHandler(cols, rows) {
		sortedArray.sort(compareId);
		var newTable = createTable(cols, rows);
		fillingTable(newTable, sortedArray, cols, rows);
		addListenersToColsButtons(cols, rows);

		function compareId(goodA, goodB) {
			return goodA.id - goodB.id;
		}
	}

	function hideForm() {
		d.getElementsByTagName("form")[0].style.display = "none";
	}

	function showForm() {
		d.getElementsByTagName("form")[0].style.display = "inline";
	}

	function hideInputFields() {
		var labels = d.getElementsByTagName("label");

		if(arguments.callee.caller.name == "handler1") {
			labels[2].style.display = "none";
			labels[3].style.display = "none";
			qualityField.style.display = "none";
			idField.style.display = "none";
		}

		if(arguments.callee.caller.name == "handler2") {
			labels[3].style.display = "none";
			idField.style.display = "none";
		}	
	}

	function showInputFields() {
		var labels = d.getElementsByTagName("label");

		labels[2].style.display = "inline";
		labels[3].style.display = "inline";
		qualityField.style.display = "inline";
		idField.style.display = "inline";
	}

	function hideButtons() {
		button1.style.display = "none";
		button2.style.display = "none";
		button3.style.display = "none";
	}

	function showButtons() {
		button1.style.display = "inline";
		button2.style.display = "inline";
		button3.style.display = "inline";
	}

	function hideReturnBackButton() {
		returnBackButton.style.display = "none";
	}

	function showReturnBackButton() {
		returnBackButton.style.display = "inline";
	}

	function addListenersToColsButtons(cols, rows) {

		var name = d.getElementById("name"),
			price = d.getElementById("price"),
			quality = d.getElementById("quality"),
			id = d.getElementById("id");

		if(name !== null) {
			name.addEventListener("click", function() {
				sortNameHandler(cols, rows);
			});
		}

		if(price !== null) {		
			price.addEventListener("click", function() {
				sortPriceHandler(cols, rows);
			});
		}

		if(quality !== null) {
			quality.addEventListener("click", function() {
				sortQualityHandler(cols, rows);
			});
		}

		if(id !== null) {
			id.addEventListener("click", function() {
				sortIdHandler(cols, rows);
			});
		}
	}
}