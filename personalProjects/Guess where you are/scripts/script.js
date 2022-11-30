	$("#stage").click(function(){nextStage();});
	/**
		Obiect care memoreaza lista cu linkuri corespunzatoare unei anumite zone geografice,
		obtinute din fisierul countries.js, prin intermediul variabilei jsonList
	*/
	class coordinateList{
		/**
			* @param {string} name Numele Zonei geografice care va fi adaugata in lista
		*/
        constructor(name){
            if(name == "")
                this.list = [];
            else
                this.list = jsonList[name];
			//Folosim un vector de frecventa pentru a nu folosi aceleasi coordonate de mai multe ori
            this.usedList = [];
            this.usedLinks = 0;
            for(var i = 0; i < this.list.length; i++){
                this.usedList.push(false);
            }
        }
		/**
			* @return {string} Un link catre StreetView la coordonate aleatorii
		*/
        getRandomLink(){
            var randomIndex;
            do{
                randomIndex = Math.floor(Math.random() * this.list.length);
            }while(this.usedList[randomIndex] == true);
            this.usedLinks++;
            if(this.usedLinks == this.usedList.length){
				//Dupa ce am folosit toate linkurile posibile, resetam vectorul de frecventa
                for(var i = 0; i < this.usedList.length; i++){
                    this.usedList[i] = false;
                }
                this.usedLinks = 1;
            }
            this.usedList[randomIndex] = true;
            return this.list[randomIndex];
        }
		/**
			* @param {coordinateList} otherList O alta lista de linkuri care va fi concatenata cu lista pe care o avem deja
		*/ 
        addOtherList(otherList){
            this.list = this.list.concat(otherList.list);
            this.usedList = this.usedList.concat(otherList.usedList);
            this.usedLinks += otherList.usedLinks;
        }
    };
	
	//Initializam listele cu linkuri, din fisierul JSON
	var europeList = new coordinateList("europe");
	var asiaList = new coordinateList("asia");
	var africaList = new coordinateList("africa");

	var worldList = new coordinateList("");
	worldList.addOtherList(europeList);
	worldList.addOtherList(africaList);
	worldList.addOtherList(asiaList);
	
	var selectedLat = 0, selectedLng = 0; //Coordonatele selectate de utilizator
    var correctLat, correctLng; //Coordonatele corecte
    var finishedGame = false;
    var progressBar;
    var score = 0;
    var stage = 0;
	
	//Comanda de initializare a primelor coordonate
	updateCorrectLatLng();
	
	//Initializam plugin-ul pentru harta
    var mymap = L.map('mapid').setView([30, -31], 1);
    L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
        minZoom: 1,
        id: 'mapbox.streets'
    }).addTo(mymap);
    //Definim un marker personalizat, asemanator cu cel deja existent
    var purpleIcon = L.icon({
        iconUrl: "resources/birtoiu_vasile.png",
        shadowUrl: "leaflet/images/marker-shadow.png",
        iconSize: [25, 41],
        iconAnchor: [13, 41]
    });
    //Variabile care ne vor ajuta in controlarea plugin-ului
    var lastMarker = null;
	var correctMarker = null;
    var polyline;
	
    function onMapClick(e) {
		$("#buttonid").prop("disabled", false); //Odata ce utilizatorul a facut prima presupunere, activam butonul de confirmare
		//Verificam daca utilizator si-a confirmat raspunsul, astfel nemaiputand sa apese pe harta
        if (finishedGame == false) {
            selectedLat = e.latlng.lat;
            selectedLng = e.latlng.lng % 360; //In cazul in care utilizatorul trage harta in lateral, iar aceasta se repeta, trebuie sa luam longitudinea intre -180 si 180 de grade
			/* Folosim o formula in functie de jumatatea circumferintei pamantului, adica 20000 Km, pentru a calcula
			   un procent care reprezinta cat de aproape a fost utilizatorul de raspunsul corect */
            progressBar = 100 - ((getDistance(correctLat, correctLng, selectedLat, selectedLng) / 20000) * 100);
            $("#distance").text(getDistance(correctLat, correctLng, selectedLat, selectedLng).toFixed(0) + " km");
            if (lastMarker != null)
                lastMarker.remove();
            lastMarker = L.marker([e.latlng.lat, e.latlng.lng], {icon: purpleIcon}).addTo(mymap);
        }

    }
    mymap.on('click', onMapClick);
       
    $("#mapid, #buttonid").mouseenter(function () {
		//Daca harta este in stagiul de raspuns confirmat, nu mai este cazul sa fie animata
        if (finishedGame)
            return;
        $("#mapid").stop().animate({
            opacity: 1,
            width: "500px",
            height: "300px"
        }, 1000
		);
        $("#buttonid").stop().animate({
            opacity: 1,
            width: "500px"
        }, 1000
        );
    });
    $("#mapid, #buttonid").mouseleave(function () {
		//Daca harta este in stagiul de raspuns confirmat, nu mai este cazul sa fie animata
        if (finishedGame)
            return;
        $("#mapid").stop().animate({
            opacity: 0.50,
            width: "400px",
            height: "240px"
        }, 1000
        );
        $("#buttonid").stop().animate({
            opacity: 0.75,
            width: "400px",
            right: "10px"
        }, 1000
        );
    });
	/**
		Functie care se ocupa cu ansamblul de animatii si functionalitati ale ecranului de confirmare raspuns
	*/
    function showResult() {
        finishedGame = true;
        $("#buttonid").prop("disabled", true); //Pregatim butonul de confirmare pentru urmatoarea runda
        $("#result_popup").css("display", "block"); //Scoatem proprietatea de hidden de pe acest element de fundal
        $("#result_popup").animate({
            opacity: 0.75
        }, 1000, function () {
            mymap.invalidateSize(); //Fortam harta sa detecteze schimbarea marimii
        });
        $("#buttonid").stop().animate({
            opacity: 1,
            width: "60%",
            height: "70%",
            right: "20%",
            bottom: "10%"
        }, 1000
		);
        $("#progress").stop().delay( 800 ).animate({
            opacity: 1
        }, 1000, function(){
            $("#score").text("Score: " + score.toFixed(0));
        });
        $("#stage").stop().delay(1500).animate({
            opacity: 1
        }, 1000
		);
        $("#distance").stop().delay(1500).animate({
            opacity: 1
        }, 1000
		);
        $("#bar").stop().delay(1500).animate({
            width: (progressBar + '%'),
        }, 1000
		);
        $("#mapid").stop().animate({
            opacity: 1,
            width: "60%",
            height: "60%",
            bottom: "20%",
            right: "20%"
        }, 1000, function () {
			//Vezi descrierea functiei
            if (goAroundGlobe()) {
                if (correctLng < selectedLng)
                    correctLng += 360;
                else
                    correctLng -= 360;
            }
            correctMarker = L.marker([correctLat, correctLng]).addTo(mymap); //Adaugam pe harta raspunsul correct
            lastMarker.remove();
            lastMarker = L.marker([selectedLat, selectedLng], { icon: purpleIcon }).addTo(mymap);
			//Trasam o linie intre coordonatele selectate si cele corecte
            polyline = L.polyline(
                [[correctLat, correctLng],
                [selectedLat, selectedLng]],
                { color: 'purple' }).addTo(mymap);
			//Incardram linia pe harta
            mymap.fitBounds(polyline.getBounds(), {padding: [5, 5]});
		});
		
        stage++;

        if (stage == 5) {
            $("#stage").text("See Score");
			$("#stage").off("click");
            $("#stage").click(function () { showScore(); });
        }
		
        score += (progressBar.toFixed(2) * 100);
    }
	
	
	/**
		Functie care se ocupa cu resetarea elementelor, pentru a putea trece la urmatoarea runda
	*/
    function nextStage() {
        updateCorrectLatLng();
        correctMarker.remove();
        $("#result_popup").css("display", "none"); //Ascundem elementul de fundal
        $("#result_popup").animate({
            opacity: 0
        }, 1000, function () {
            $("#stageid").text("Stage: " + (stage + 1) + "/5");
        });
        $("#buttonid").stop().delay(800).animate({
            width: "400px",
            height: "43px",
            right: "10px",
            bottom: "1.70%"
        }, 1000
		);
        $("#progress").stop().animate({
            opacity: 0
        }, 1000
		);
        $("#bar").stop().animate({
            width: (0 + '%')
        }, 1000
		);
        $("#stage").stop().animate({
            opacity: 0
        }, 1000
		);
        $("#distance").stop().animate({
            opacity: 0
        }, 1000
		);
        $("#mapid").stop().delay(800).animate({
            width: "400px",
            height: "240px",
            right: "10px",
            bottom: "9%"
        }, 1000, function () {
			mymap.invalidateSize(); //Fortam harta sa detecteze schimbarea marimii
			mymap.setView([30, -31], 1);
            finishedGame = false;
            $("#mapid").stop().animate({
                opacity: "0.5"
            }, 1000
			);
            $("#buttonid").stop().animate({
                opacity: "0.75",
            }, 1000
			);
        });
        lastMarker.remove();
        polyline.remove();
    }
    
    function degreesToRadians(degrees) {
        return degrees * Math.PI / 180;
    }
    const earthRadiusKm = 6371;
	/**
		Calculeaza distanta intre doua coordonate geografice
		* @param {number} lat1 Prima latitudine
		* @param {number} lng1 Prima longitudinea
		* @param {number} lat2 A doua latitudine
		* @param {number} lng2 A doua longitudinea
		* @return Distanta fizica in kilometri
	*/
    function getDistance(lat1, lng1, lat2, lng2) {

        var dLat = degreesToRadians(lat2 - lat1);
        var dLon = degreesToRadians(lng2 - lng1);

        lat1 = degreesToRadians(lat1);
        lat2 = degreesToRadians(lat2);

        var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
        var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        return earthRadiusKm * c;
    }

	/**
		* @return Verificam daca o linie mai scurta ar putea fi prin cealalta parte a pamantului
	*/
    function goAroundGlobe() {
        var lngDistance = Math.abs(selectedLng - correctLng);
        return lngDistance > 180;
    }
	
	
	
	function updateCorrectLatLng(){
		//Ne folosim de proprietatea window.name pentru a transmite intre pagini variabila responsabila pentru regiunea selectata
		if(window.name == "world")
			var streetViewLink = worldList.getRandomLink();
		else if(window.name == "europe")
			var streetViewLink = europeList.getRandomLink();
		else if(window.name == "asia")
			var streetViewLink = asiaList.getRandomLink();
		else if(window.name == "africa")
			var streetViewLink = africaList.getRandomLink();
		else 
			var streetViewLink = worldList.getRandomLink();
		$("#iframe").attr("src",streetViewLink);
		//Folosim o expresie regulata pentru a extrage coordonatele din linkul de streetview
		var rgx = new RegExp('1d(-?[0-9]+\.[0-9]+).+2d(-?[0-9]+\.[0-9]+)');
		var rgxResult = streetViewLink.match(rgx);
		correctLat = Number(rgxResult[1]);
		correctLng = Number(rgxResult[2]);
	}
	
	
	function showScore() {
		console.log("ma lingi in pizda");
	    $("#progress").stop().animate({
	        opacity: 0
	    }, 1000
		);
        $("#stage").stop().animate({
	                opacity: 0
	            }, 1000
				);
	    $("#distance").stop().animate({
	                opacity: 0
	            }, 1000
				);
	    $("#bar").stop().animate({
	        width: (0 + '%')
	    }, 1000, function () {
	        $("#congrats").text("You've accumulated a score of " + score.toFixed(0));
	        $("#distance").text("Home");
	        $("#distance").css("cursor", "pointer");
			$("#distance").off("click");
	        $("#distance").click(function () { location.replace("index.html"); });
	        $("#stage").text("Play Again");
			$("#stage").off("click");
	        $("#stage").click(function () { playAgain(); });
	        $("#distance").stop().animate({
	            opacity: 1
	        }, 1000
			);
	        $("#congrats").stop().animate({
	            opacity: 1
	        }, 1000
			);
	        $("#stage").stop().animate({
	            opacity: 1
	        }, 1000
			);
	    });
	}

	function playAgain() {
	    correctMarker.remove();
	    $("#result_popup").css("display", "none");
	    $("#result_popup").animate({
	        opacity: 0
	    }, 1000
		);
	    $("#buttonid").stop().delay(800).animate({
	        width: "400px",
	        height: "43px",
	        right: "10px",
	        bottom: "1.70%"
	    }, 1000
		);
	    $("#stage").stop().animate({
	        opacity: 0
	    }, 1000
		);
	    $("#congrats").stop().animate({
	        opacity: 0
	    }, 1000
		);
	    $("#distance").stop().animate({
	        opacity: 0
	    }, 1000
		);
	    $("#mapid").stop().delay(800).animate({
	        width: "400px",
	        height: "240px",
	        right: "10px",
	        bottom: "9%"
	    }, 1000, function () {
	        mymap.invalidateSize();
	        mymap.setView([30, -31], 1);
	        finishedGame = false;
	        $("#mapid").stop().animate({
	            opacity: "0.5"
	        }, 1000, function () {
	        });
	        $("#buttonid").stop().animate({
	            opacity: "0.75",
	        }, 1000, function () {

	        });
	        updateCorrectLatLng();
	        $("#stage").text("Next Stage");
			$("#stage").off("click");
	        $("#stage").click(function () { nextStage(); });
	        $("#distance").text("");
	        $("#score").text("Score: 0");
	        $("#stageid").text("Stage: 1/5");
	        score = 0;
	        stage = 0;
	    });
	    lastMarker.remove();
	    polyline.remove();
	}	

	function chooseCategory(category) {
		if(category == 1) 
			window.name = "world";
		else if(category == 2)
			window.name = "europe";
		else if(category == 3)
			window.name = "asia";
		else if(category == 4)
			window.name = "africa";
		location.replace("game.html");
	}

	
	
	
    
    