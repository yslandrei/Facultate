func = (fromList, toList) => {
    return (ev) => {
        const selItemIdx = fromList.selectedIndex;
        if (selItemIdx === -1) {
            return;
        }
        toList.appendChild(fromList[selItemIdx]);
        fromList.selectedIndex = -1;
    }
}
const firstList = document.getElementById("firstList");
const secondList = document.getElementById("secondList");

firstList.onclick = func(firstList, secondList);
secondList.onclick = func(secondList, firstList);