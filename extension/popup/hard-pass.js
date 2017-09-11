function getTabDomain(tab) {
    const url = new URL(tab.url);
    const hostname = url.hostname;
    const domain = psl.parse(hostname).domain;
    return domain;
}

const passwordCharacters = ("abcdefghilklmnopqrstuvwxyz" +
    "ABCDEFGHILKLMNOPQRSTUVWXYZ" +
    "0123456789!@#$%^&*_+:,.?").split("")

const domainAliases = [
    ["ameritrade.com", "tdameritrade.com"],
    ["bankofamerica.com", "bofa.com", "mbna.com", "usecfo.com"],
    ["sprint.com", "sprintpcs.com", "nextel.com"],
    ["google.com", "youtube.com", "gmail.com", "youtube.fr", "google.fr", "gmail.fr", "youtube.ch", "google.ch", "gmail.ch"],
    ["apple.com", "icloud.com"],
    ["wellsfargo.com", "wf.com"],
    ["southerncompany.com", "southernco.com"],
    ["mymerrill.com", "ml.com", "merrilledge.com"],
    ["accountonline.com", "citi.com", "citibank.com", "citicards.com", "citibankonline.com"],
    ["cnet.com", "cnettv.com", "com.com", "download.com", "news.com", "search.com", "upload.com"],
    ["bananarepublic.com", "gap.com", "oldnavy.com", "piperlime.com"],
    ["bing.com", "hotmail.com", "live.com", "microsoft.com", "msn.com", "passport.net", "windows.com"],
    ["ua2go.com", "ual.com", "united.com", "unitedwifi.com"],
    ["overture.com", "yahoo.com", "flickr.com"],
    ["zonealarm.com", "zonelabs.com"],
    ["paypal.com", "paypal-search.com"],
    ["avon.com", "youravon.com"],
    ["diapers.com", "soap.com", "wag.com", "yoyo.com", "beautybar.com", "casa.com", "afterschool.com", "vine.com", "bookworm.com", "look.com", "vinemarket.com"],
    ["1800contacts.com", "800contacts.com"],
    ["amazon.com.au"],
    ["express-scripts.com", "medcohealth.com"],
    ["cox.com", "cox.net", "coxbusiness.com"],
    ["mynortonaccount.com", "norton.com"],
    ["verizon.com", "verizon.net"],
    ["logmein.com", "logme.in"],
    ["rakuten.com", "buy.com"],
    ["siriusxm.com", "sirius.com"],
    ["ea.com", "origin.com", "play4free.com", "tiberiumalliance.com"],
    ["37signals.com", "basecamp.com", "basecamphq.com", "highrisehq.com"],
    ["steampowered.com", "steamcommunity.com"],
    ["chart.io", "chartio.com"],
    ["gotomeeting.com", "citrixonline.com"],
    ["gogoair.com", "gogoinflight.com"],
    ["mysql.com", "oracle.com"],
    ["discover.com", "discovercard.com"],
    ["dcu.org", "dcu-online.org"],
    ["nefcuonline.com", "nefcu.com"],
    ["healthcare.gov", "cms.gov"],
    ["pepco.com", "pepcoholdings.com"],
    ["century21.com", "21online.com"],
    ["comcast.com", "comcast.net", "xfinity.com"],
    ["cricketwireless.com", "aiowireless.com"],
    ["mandtbank.com", "mtb.com"],
    ["dropbox.com", "getdropbox.com"],
    ["snapfish.com", "snapfish.ca"],
    ["alibaba.com", "aliexpress.com", "aliyun.com", "net.cn", "www.net.cn"],
    ["playstation.com", "sonyentertainmentnetwork.com"],
    ["mercadolivre.com", "mercadolivre.com.br", "mercadolibre.com", "mercadolibre.com.ar", "mercadolibre.com.mx"],
    ["taobao.com", "tmall.com", "alimama.com", "1688.com"],
    ["zendesk.com", "zopim.com"],
    ["healthfusion.com", "healthfusionclaims.com"],
    ["autodesk.com", "tinkercad.com"],
    ["railnation.ru", "railnation.de", "rail-nation.com", "railnation.gr", "railnation.us", "trucknation.de", "traviangames.com"],
    ["wpcu.coop", "wpcuonline.com"],
    ["mathletics.com", "mathletics.com.au", "mathletics.co.uk"],
    ["discountbank.co.il", "telebank.co.il"],
    ["mi.com", "xiaomi.com"],
    ["postepay.it", "poste.it"],
    ["facebook.com", "messenger.com"],
    ["skysports.com", "skybet.com", "skyvegas.com"],
    ["disneymoviesanywhere.com", "go.com", "disney.com", "dadt.com"],
    ["soundcu.com", "netteller.com"],
    ["pokemon-gl.com", "pokemon.com"],
    ["myuv.com", "uvvu.com"],
    ["bank-yahav.co.il", "bankhapoalim.co.il"],
    ["mdsol.com", "imedidata.com"],
    ["volvooceanrace.com", "virtualregatta.com"],
    ["mycanal.fr", "canal-plus.com"],
    ["sanguosha.com", "bianfeng.com"],
    ["sears.com", "shld.net"],
    ["trsretire.com", "divinvest.com"],
    ["norsk-tipping.no", "buypass.no"],
    ["my-bookings.org", "my-bookings.cc"],
    ["skygo.co.nz", "skytv.co.nz"],
    ["altra.org", "altraonline.org"],
    ["xiami.com", "alipay.com"],
    ["belkin.com", "seedonk.com"],
    ["mysmartedu.com", "mysmartabc.com"],
    ["applefcu.org", "applefcuonline.org"],
    ["bancomer.com", "bancomer.com.mx", "bbvanet.com.mx"],
    ["turbotax.com", "intuit.com"],
    ["shopify.com", "myshopify.com"],
    ["onlineatnsb.com", "norwaysavingsbank.com"],
    ["concur.com", "concursolutions.com"],
    ["ebay.ca", "ebay.in", "ebay.com.au"],
    ["techdata.com", "techdata.ch"],
    ["schwab.com", "schwabplan.com"],
    ["hvfcu.org", "hvfcuonline.org"],
    ["firefox.com", "mozilla.org"],
    ["tesla.com", "teslamotors.com"],
    ["morganstanley.com", "morganstanleyclientserv.com", "stockplanconnect.com", "ms.com"],
    ["ebay.com", "gixen.com", "ebay.fr", "ebay.co.uk", "ebay.de"],
    ["amazon.com", "amazon.co.uk", "amazon.ca", "amazon.es", "amazon.it", "amazon.fr", "amazon.de"],
    ["t411.io", "t411.in", "t411.li", "t411.ai", "t411.al"]
]
const aliasForDomain = {}
for (const aliasGroup of domainAliases) {
    for (const domain of aliasGroup) {
        aliasForDomain[domain] = aliasGroup[0];
    }
}

const defaultPasswordLength = 12
const passwordLengthExceptions = {
    'google.com': 32,
    'facebook.com': 32,
    'linkedin.com': 32,
    'wordpress.com': 32,
    'postfinance.ch': 32,
    'ubs.ch': 32,
    'paypal.com': 20,
    'bankofamerica.com': 20,
    'microsoft.com': 16,
}

let domain = browser.tabs.query({
        active: true,
        currentWindow: true
    })
    .then(tabs => getTabDomain(tabs[0]))
    .then(domain => {
        return aliasForDomain[domain] || domain;
    })
    .then(domain => {
        document.getElementById('domain-output').value = domain;
        return domain;
    });


function hashToPassword(hash, domain) {
    let password = ""
    let passwordLength = passwordLengthExceptions[domain] || defaultPasswordLength;
    for (i = 0; i < passwordLength; i++) {
        const hex = "0x" + hash[(2 * i) % hash.length] + hash[(2 * i + 1) % hash.length]
        const characterIndex = parseInt(hex) % passwordCharacters.length;
        password += passwordCharacters[characterIndex];
    }
    return password;
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
            } else {
                throw new Error("No payload found in JSON")
            }
        })
}

const generatePasswordButton = document.querySelector("#generate-password-button");
generatePasswordButton.addEventListener("click", (e) => {
    browser.tabs.executeScript(null, {
            file: '/content_scripts/browser-polyfill.js'
        })
        .then(() => browser.tabs.executeScript(null, {
            file: '/content_scripts/insert_password.js'
        }))
        .then(() => browser.tabs.query({
            active: true,
            currentWindow: true
        }))
        .then((tabs) => {
            const activeTab = tabs[0]
            const variant = document.querySelector("#variant-input").value;
            return Promise.all([activeTab, domain, variant])
        })
        .then(([activeTab, domain, variant]) => Promise.all([activeTab, domain, askHash(domain, variant)]))
        .then(([activeTab, domain, hash]) => [activeTab, hashToPassword(hash, domain)])
        .then(([activeTab, password]) => browser.tabs.sendMessage(activeTab.id, password))
        .catch(console.log)
});