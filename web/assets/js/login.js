
function readBody(xhr) {
  var data;
  if (!xhr.responseType || xhr.responseType === "text") {
    data = xhr.responseText;
  } else if (xhr.responseType === "document") {
    data = xhr.responseXML;
  } else {
    data = xhr.response;
  }
  return data;
}


function doLogin() {
  var url = "sapphire-api/lobby/login";
  var params = "{\"username\":\"" + document.getElementsByName('username')[0].value + "\",\"pass\":\"" + document.getElementsByName('password')[0].value + "\"}";
  var xhr = new XMLHttpRequest();
  xhr.open("POST", url, true);

  xhr.onreadystatechange = function() {
    if (xhr.readyState == 4) {
      try {
        var response = readBody(xhr);
        var parsed = JSON.parse(response);
        window.external.Boot(parsed.sId, parsed.lobbyHost, parsed.frontierHost);
      } catch(err) {
        document.getElementById("Error").innerHTML = "Login failed.";
      }
    }
  }
  
  xhr.send(params);
}


function keypressing(e) {
  if (!e) e = window.event;
  var keyCode = e.keyCode || e.which;
  if (keyCode == '13'){
    doLogin();
    return false;
  }
}

document.getElementsByName('password')[0].addEventListener('keypress', function(event) {
  return keypressing(event);
});
document.getElementById('submitButton').addEventListener('click', doLogin);
