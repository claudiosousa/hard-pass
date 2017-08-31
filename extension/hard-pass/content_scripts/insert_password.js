new Promise((resolve, reject) => {
        input = document.querySelector('input[type="password"]')
        if (input)
            resolve(input)
        else
            reject('No password input found')
    })
    .then((input) => Promise.all([input, fetch('http://127.0.0.1:9876', {
        method: 'POST',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify({
            'payload': window.location.hostname
        })
    })]))
    .then(([input, response]) => {
        // var contentType = response.headers.get("content-type")
        // if (contentType && contentType.includes("application/json")) {
        //     return [input, response.json()]
        // }
        // throw new TypeError("Response is not JSON")
        return Promise.all([input, response.json()])
    })
    .then(([input, json]) => {
        if ('payload' in json) {
            input.value = json.payload
        }
        else {
            throw new Error("No payload found in JSON")
        }
    })
    .catch(console.log)
