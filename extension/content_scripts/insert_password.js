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
            'payload': psl.parse(window.location.hostname).domain + '\nsome variant'
        })
    })]))
    .then(([input, response]) => Promise.all([input, response.json()]))
    .then(([input, json]) => {
        if ('payload' in json) {
            input.value = json.payload
        }
        else {
            throw new Error("No payload found in JSON")
        }
    })
    .catch(console.log)
