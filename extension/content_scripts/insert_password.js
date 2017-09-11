function findPasswordInput() {
    return document.querySelector('input[type="password"]'+
                                  ':not([style*="display:none"])'+
                                  ':not([style*="display: none"])');
}

function insertPassword(password) {
    const passwordInput = findPasswordInput();
    if (passwordInput) {
        passwordInput.value = password;
    }
}
browser.runtime.onMessage.addListener(insertPassword);
