import requests
import json
import pprint
import getinfo

pp = pprint.PrettyPrinter(indent=4)

# POST 요청을 보낼 URL
url = 'https://www.inhatc.ac.kr/haksa/kr/getHaksaFoodMenuList.do'

headers = {
    'Host': 'www.inhatc.ac.kr',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    'Accept': '*/*',
    'Accept-Language': 'ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7',
    'Accept-Encoding': 'gzip, deflate, br',
    'Connection': 'keep-alive',
    'Content-Length': '58',
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
    'Origin': 'https://www.inhatc.ac.kr',
    'Referer': 'https://www.inhatc.ac.kr/kr/485/subview.do',
    'X-Requested-With': 'XMLHttpRequest'
}

monday, saturday = getinfo.menuDates();

# 요청에 포함할 데이터
rqdata = {
    "gubun": '학생',
    "strDate": monday,
    "endDate": saturday
}

# POST 요청 보내기
response = requests.post(url, headers=headers, data=rqdata)

# 응답 데이터 확인
if response.status_code == 200:
    print("HTTP Response Status : 200\n")
    rpdata = response.json()
    
    # Lagacy CODE
    '''
    for i in range(len(rpdata)):
        for key in rpdata[i]:
            if isinstance(rpdata[i][key], str):
                rpdata[i][key] = rpdata[i][key].replace('\r\n', ', ')
    '''  
    # 성능 개선 
    for item in rpdata:
        for key, value in item.items():
            if isinstance(value, str):
                item[key] = value.replace('\r\n', ', ')

with open(monday + '-' + rpdata[-1]['date'] + '_menu'+ '.json', 'w', encoding='utf-8') as json_file:
    json.dump(rpdata, json_file, ensure_ascii=False, indent=4)
    
with open('api/inhatc_menu.json', 'w', encoding='utf-8') as json_file:
    json.dump(rpdata, json_file, ensure_ascii=False, indent=4)
    
pp.pprint(rpdata);