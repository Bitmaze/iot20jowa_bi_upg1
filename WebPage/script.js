let tabledata = document.getElementById('tabledata')

setInterval(() => {
    tabledata.innerHTML = "";

    fetch("https://iot20jowafunc.azurewebsites.net/api/GetCosmosData?")
    .then(res => res.json())
    .then(data => {
        for(let row of data) {
            tabledata.innerHTML += `<tr><td>${row.dId}</td><td>${row.lts}</td><td>${row.tmp}</td><td>${row.hum}</td><td>${row.light}</td>`
        }
    })   
}, 5000);

