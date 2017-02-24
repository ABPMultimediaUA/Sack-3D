/*Creamos las funciones ajax para simplificar el codigo*/
function createAjax(){
    var xmlhttp;
    if(window.XMLHttpRequest) { // Objeto nativo
        xmlhttp = new XMLHttpRequest(); // Se obtiene el nuevo objeto
    } else if (window.ActiveXObject) { // IE(Windows): objecto ActiveX
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlhttp; 
} 
var j=0;

function igdb(){

            var ajax = createAjax();
             var url = "https://igdbcom-internet-game-database-v1.p.mashape.com/games/?fields=*&limit=50&order=name&offset="+j+" "
             console.log(url);
             if(ajax){
              ajax.onreadystatechange = procesarCambio;
              
              ajax.open("GET", url, true);
              ajax.setRequestHeader("X-Mashape-Key", "l75yqzAZyVmshBB70018LMfrb7vMp15hRk5jsnLPK9ZNp4iMp1");
              ajax.setRequestHeader("Accept", "application/json");
              ajax.send();
             }

              function procesarCambio(){
               if(ajax.readyState==4){
                if(ajax.status==200){
                 
                 var respuesta = window.JSON.parse(ajax.responseText);
                     for (var i = 0; i < respuesta.length; i++) {
                         console.log(respuesta[i].name);
                     }

                     j+=50;
                     if(j<400){igdb();}
                     else{terminar();}
                }
               }
              }
}

function terminar(){
    console.log("fin del juego");
}