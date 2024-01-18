unction fetchRecentActivity() {
  var url = "https://api.github.com/repos/SapphireMordred/Sapphire/events";
  var xhr = new XMLHttpRequest();
  xhr.open("GET", url, true);

  xhr.onreadystatechange = function() {
    if (xhr.readyState == 4 && xhr.status == 200) {
      var response = JSON.parse(xhr.responseText);
      var commitLog = document.getElementById("commit-log");

      for (var i = 0; i < response.length; i++) {
        var commit = response[i];
        var commitItem = document.createElement("li");
        commitItem.innerHTML = commit.type + " - " + commit.actor.login;
        commitLog.appendChild(commitItem);
      }
    }
  }

  xhr.send();
}

// Call the fetchRecentActivity function when the page loads
window.onload = function() {
  fetchRecentActivity();
};
