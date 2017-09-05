function getTabDomain(tab) {
    const url = new URL(tab.url)
    const hostname = url.hostname
    const domain = psl.parse(hostname).domain
    return domain
}

function hashToPassword(hash) {
    return hash
}

function askHash(domain, variant) {
    const payload = domain + '\n' + variant
    return fetch('http://127.0.0.1:9876', {
        method: 'POST',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify({
            'payload': payload
        })
    })
    .then(response => response.json())
    .then(json => {
        if ('payload' in json) {
            return json.payload
        }
        else {
            throw new Error("No payload found in JSON")
        }
    })
}

const generatePasswordButton = document.querySelector("#generate-password-button");
generatePasswordButton.addEventListener("click", (e) => {
    browser.tabs.executeScript(null, { file: '/content_scripts/browser-polyfill.js' })
    .then(() => browser.tabs.executeScript(null, { file: '/content_scripts/insert_password.js' }))
    .then(() => browser.tabs.query({active: true, currentWindow: true}))
    .then((tabs) => {
        const activeTab = tabs[0]
        const domain = getTabDomain(activeTab)
        const variant = document.querySelector("#variant-input").value
        return [activeTab, domain, variant]      
    })
    .then(([activeTab, domain, variant]) => Promise.all([activeTab, askHash(domain, variant)]))
    .then(([activeTab, hash]) => [activeTab, hashToPassword(hash)])
    .then(([activeTab, password]) => browser.tabs.sendMessage(activeTab.id, password))
    .catch(console.log)
});
