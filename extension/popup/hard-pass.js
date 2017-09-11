function getTabDomain(tab) {
    const url = new URL(tab.url)
    const hostname = url.hostname
    const domain = psl.parse(hostname).domain
    return domain
}

const passwordCharacters = ("abcdefghilklmnopqrstuvwxyz" +
                            "ABCDEFGHILKLMNOPQRSTUVWXYZ" +
                            "0123456789!@#$%^&*_+:,.?").split("")

const defaultPasswordLength = 12
const passwordLengthExceptions = {
    'google.com': 32,
    'gmail.com': 32,
    'youtube.com': 32,
    'facebook.com': 32,
    'linkedin.com': 32,
    'wordpress.com': 32,
    'postfinance.ch': 32,
    'ubs.ch': 32,
    'paypal.com': 20,
    'bankofamerica.com': 20,
    'microsoft.com': 16, 
    'microsoftonline.com': 16, 
    'outlook.com': 16,
    'hotmail.com': 16,
    'live.com': 16,
    'azure.com': 16,
}

function hashToPassword(hash, domain) {
    let password = ""
    let passwordLength = passwordLengthExceptions[domain] || defaultPasswordLength;
    for (i=0; i<passwordLength; i++) {
        const hex = "0x" + hash[(2*i) % hash.length] + hash[(2*i + 1) % hash.length]
        const characterIndex = parseInt(hex) % passwordCharacters.length
        password += passwordCharacters[characterIndex] 
    }
    return password
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
    .then(([activeTab, domain, variant]) => Promise.all([activeTab, domain, askHash(domain, variant)]))
    .then(([activeTab, domain, hash]) => [activeTab, hashToPassword(hash, domain)])
    .then(([activeTab, password]) => browser.tabs.sendMessage(activeTab.id, password))
    .catch(console.log)
});
