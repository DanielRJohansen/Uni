(window.webpackJsonp=window.webpackJsonp||[]).push([[5,7],{103:function(e,t,n){"use strict";n.d(t,"c",(function(){return g.f})),n.d(t,"d",(function(){return g.g})),n.d(t,"b",(function(){return g.d})),n.d(t,"a",(function(){return g.a}));var r=n(2),i=n.n(r),a=n(1),o=n.n(a),s=n(42),c=n(90),u=n(168),f=n.n(u),d=n(73),l=function(e){function t(t){var n;n=e.call(this)||this;var r=t.category,i=t.clientName,a=t.transport;if(!r)throw new Error("required category is missing");if(n.category=r,!i)throw new Error("required clientName is missing");if(n.clientName=i,"function"!=typeof a)throw new Error("Invalid transport: "+a);return n._transport=a,n}f()(t,e);var n=t.prototype;return n.createEventObject=function(e,t,n){return i()({_category_:t,triggered_on:Date.now(),event_namespace:e},n)},n._handleError=function(e){try{this.emit("error",e)}catch(e){}throw e},n.log=function(e,t){var n=this.createEventObject(i()({client:this.clientName},e),this.category,t);this.emit("log",n),this._log(n)},n._log=function(e){var t=this;e&&this._transport(e).catch((function(e){return t._handleError(e)})).catch((function(){}))},t}(n.n(d).a),h=function(e){var t=new l(e);return t.on("log",(function(e){Object(s.a)("[scribe] LOG "+Object(c.b)(e.event_namespace),e)})),t.on("error",(function(e){Object(s.a)("[scribe] ERROR",e)})),t},m=n(43),p=n.n(m),j=n(64),v=function(e){var t={l:JSON.stringify(e)},n=e.dnt?{dnt:1}:{},r=j.a.isBucketed()?j.a.getSessionId():{};return i()({},t,n,r)},E=function(){return function(e){return t=v(e),n="https://syndication.twitter.com/i/jot?"+p.a.stringify(t),new Promise((function(e,t){var r=document.createElement("img");r.addEventListener("load",(function(){return e(r)})),r.addEventListener("error",t),r.src=n}));var t,n}},g=n(59),_=function(){function e(){o()(this,"_data",{context:g.c}),this._scribeClient=h({clientName:g.b,category:"tfw_client_event",transport:E()})}var t=e.prototype;return t.initialize=function(e){this._page=e.page,this._data=i()({},this._data,e.data)},t.scribe=function(e,t,n){this._scribeClient.log(i()({page:this._page,action:e},t),i()({},this._data,n))},e}();n(211),t.e=new _},109:function(e,t,n){var r={"./ar.js":[264,0,11],"./bn.js":[265,0,12],"./cs.js":[266,0,13],"./da.js":[267,0,14],"./de.js":[268,0,15],"./el.js":[269,0,16],"./en.js":[270,0,17],"./es.js":[271,0,18],"./fa.js":[272,0,19],"./fi.js":[273,0,20],"./fil.js":[274,0,21],"./fr.js":[275,0,22],"./he.js":[276,0,23],"./hi.js":[277,0,24],"./hu.js":[278,0,25],"./id.js":[279,0,26],"./it.js":[280,0,27],"./ja.js":[281,0,28],"./ko.js":[282,0,29],"./ms.js":[283,0,30],"./nb.js":[284,0,31],"./nl.js":[285,0,32],"./pl.js":[286,0,33],"./pt.js":[287,0,34],"./ro.js":[288,0,35],"./ru.js":[289,0,36],"./sv.js":[290,0,37],"./th.js":[291,0,38],"./tr.js":[292,0,39],"./uk.js":[293,0,40],"./vi.js":[294,0,41],"./zh-Hant.js":[295,0,42],"./zh.js":[296,0,43]};function i(e){if(!n.o(r,e))return Promise.resolve().then((function(){var t=new Error("Cannot find module '"+e+"'");throw t.code="MODULE_NOT_FOUND",t}));var t=r[e],i=t[0];return Promise.all(t.slice(1).map(n.e)).then((function(){return n.t(i,7)}))}i.keys=function(){return Object.keys(r)},i.id=109,e.exports=i},139:function(e,t,n){"use strict";n.d(t,"a",(function(){return r})),n.d(t,"b",(function(){return i}));var r=[],i=function(){return r.length>0}},18:function(e,t,n){"use strict";var r=n(113),i=n(22),a=n.n(i),o=n(35),s="en",c={ar:!0,fa:!0,he:!0},u=function(e){return Boolean(c[e])},f=function(e){return a.a.locales.indexOf(e)>-1};t.a={isLocaleRTL:u,isSupportedLocale:f,setLocale:function(e){return s=f(e)?e:"en",r.a.setLocale(a.a.getCldrLocale(s)).then((function(){o.default.setPreferredLanguageRTL(u(s)),document&&document.documentElement&&document.documentElement.setAttribute("lang",s)}))},getLocale:function(){return s}}},185:function(e,t,n){var r={"./ar.js":[215,0,47],"./bg.js":[216,0,48],"./bn.js":[217,0,49],"./ca.js":[218,0,50],"./cs.js":[219,0,51],"./da.js":[220,0,52],"./de.js":[221,0,53],"./el.js":[222,0,54],"./en-GB.js":[223,0,55],"./en-ss.js":[224,0,57],"./en-xx.js":[225,0,58],"./en.js":[226,0,56],"./es.js":[227,0,59],"./eu.js":[228,0,60],"./fa.js":[229,0,61],"./fi.js":[230,0,62],"./fil.js":[231,0,63],"./fr.js":[232,0,64],"./ga.js":[233,0,65],"./gl.js":[234,0,66],"./gu.js":[235,0,67],"./he.js":[236,0,68],"./hi.js":[237,0,69],"./hr.js":[238,0,70],"./hu.js":[239,0,71],"./id.js":[240,0,72],"./it.js":[241,0,73],"./ja.js":[242,0,74],"./kn.js":[243,0,75],"./ko.js":[244,0,76],"./mr.js":[245,0,77],"./ms.js":[246,0,78],"./nb.js":[247,0,79],"./nl.js":[248,0,80],"./pl.js":[249,0,81],"./pt.js":[250,0,82],"./ro.js":[251,0,83],"./ru.js":[252,0,84],"./sk.js":[253,0,85],"./sr.js":[254,0,86],"./sv.js":[255,0,87],"./ta.js":[256,0,88],"./th.js":[257,0,89],"./tr.js":[258,0,90],"./uk.js":[259,0,91],"./ur.js":[260,0,92],"./vi.js":[261,0,93],"./zh-Hant.js":[262,0,94],"./zh.js":[263,0,95]};function i(e){if(!n.o(r,e))return Promise.resolve().then((function(){var t=new Error("Cannot find module '"+e+"'");throw t.code="MODULE_NOT_FOUND",t}));var t=r[e],i=t[0];return Promise.all(t.slice(1).map(n.e)).then((function(){return n.t(i,7)}))}i.keys=function(){return Object.keys(r)},i.id=185,e.exports=i},211:function(e,t,n){"use strict";Object.freeze({FCP:"FCP",FID:"FID",LCP:"LCP"})},22:function(e,t){var n={ms:"msa",nb:"no",zh:"zh-cn","zh-Hant":"zh-tw"},r={msa:"ms",no:"nb","zh-cn":"zh","zh-tw":"zh-Hant"};e.exports={locales:["en","ar","bn","cs","da","de","el","es","fa","fi","fil","fr","he","hi","hu","id","it","ja","ko","msa","nl","no","pl","pt","ro","ru","sv","th","tr","uk","vi","zh-cn","zh-tw"],getCldrLocale:function(e){return r[e]||e},getTwitterLocale:function(e){return n[e]||e}}},350:function(e,t,n){"use strict";n.r(t);var r,i=n(89),a=n(65),o=n(38),s=n(202),c=n.n(s),u=n(710),f=n(75),d=n(8),l=n(77),h=n(64),m=n(90),p=n(76),j=n(103),v=n(92),E=new i.a(new a.a({dispatcher:o.b})),g=new i.a(new a.a({dispatcher:o.b,host:"https://syndication.twitter.com"})),_=c()(Object(u.a)()).toString();h.a.initialize(g,_);var T,b,w,k=(T=f.a.parseQueryString(location.search),b=[{key:"id",validate:function(e){return d.a.test(e)},required:!0},{key:"hideThread",accessor:function(e){return e.hideThread},validate:function(e){return["true","false"].includes(e)},transform:function(e){return"true"===e},fallback:!1},{key:"hideMedia",accessor:function(e){return e.hideCard},validate:function(e){return["true","false"].includes(e)},transform:function(e){return"true"===e},fallback:!1},d.b,d.c,d.d,d.e,d.f,d.h],Object(d.g)(T,b)),y=k.dnt,O=k.embedId,I=k.hideMedia,N=k.hideThread,L=k.id,P=k.lang,S=k.pageData,z=k.theme,C=k.widgetsVersion;j.e.initialize({page:j.c.TWEET,data:{client_version:C,dnt:y,widget_id:O,widget_origin:S.origin,widget_frame:S.frame,widget_partner:S.partner,widget_site_screen_name:S.siteScreenName,widget_site_user_id:S.siteUserId,widget_creator_screen_name:S.creatorScreenName,widget_creator_user_id:S.creatorUserId,widget_iframe_version:"251373c9:1615319843015",item_ids:[L],item_details:(r={},r[L]={item_type:m.a.TWEET},r)}}),v.c.initialize({embedId:O,data:{tweet_id:L}}),v.c.send({key:v.b.INITIALIZED,details:{iframe_version:"251373c9:1615319843015"}}),Promise.all([(w=[],window.IntersectionObserver||w.push(n.e(97).then(n.t.bind(null,1979,7))),Promise.all(w)),h.a.fetch()]).then((function(){return Object(l.a)(p.a,{lang:P,theme:z},{api:E,hideMedia:I,hideThread:N,id:L,pageData:S})}))},42:function(e,t,n){"use strict";n.d(t,"a",(function(){return r}));var r=function(e,t){0}},441:function(e,t){},442:function(e,t){},451:function(e,t){},452:function(e,t){},471:function(e,t){},473:function(e,t){},476:function(e,t){},477:function(e,t){},488:function(e,t){},49:function(e,t,n){"use strict";var r=n(18),i=n(22),a=n.n(i);t.a=function(){var e=r.a.getLocale(),t=a.a.getCldrLocale(e);return n(109)("./"+t+".js")}},59:function(e,t,n){"use strict";n.d(t,"b",(function(){return r})),n.d(t,"f",(function(){return i})),n.d(t,"g",(function(){return a})),n.d(t,"d",(function(){return o})),n.d(t,"a",(function(){return s})),n.d(t,"c",(function(){return c})),n.d(t,"e",(function(){return u}));var r="tfw",i=Object.freeze({TWEET:"tweet",DDG:"ddg"}),a=Object.freeze({FAKE:"tfw_experiment_1234",MAIN:"main",PARENT:"parent",QUOTE:"quote",PARENT_QUOTE:"parent-quote",SHARE_EXPERIMENT:"tfw_tweet_embed_share_11377"}),o=Object.freeze({AUTHOR:"author",CARD:"card",LIKE_ACTION:"like-action",LOGO:"logo",NEWS_ACTION:"news-action",PERFORMANCE:"performance",PHOTO:"photo",PLACE:"place",PRIVACY_NOTICE:"privacy-notice",PUBLIC_INTEREST_NOTICE:"public-interest-notice",SHARE_ACTION:"share-action",SOFT_INTERVENTION_PIVOT:"soft-intervention-pivot",TIMESTAMP:"timestamp",TWEET_REPLY_CONTEXT:"tweet-reply-context",TWEET_TEXT_CASHTAG:"tweet-text-cashtag",TWEET_TEXT_HASHTAG:"tweet-text-hashtag",TWEET_TEXT_MEDIA:"tweet-text-media",TWEET_TEXT_MENTION:"tweet-text-mention",TWEET_TEXT_QUOTE:"tweet-text-quote",TWEET_TEXT_URL:"tweet-text-url",VIDEO:"video",WHITESPACE:"whitespace"}),s=(Object.freeze({}),Object.freeze({CLICK_EXTERNAL:"click-external",CLICK_INTERACTIVE:"click-interactive",CLICK_TWITTER:"click-twitter",EXPERIMENT:"experiment",IMPRESSION:"impression",RESULTS:"results",NO_RESULTS:"no-results",SEEN:"seen"})),c="horizon",u={client:r,page:i.TWEET}},64:function(e,t,n){"use strict";var r=n(1),i=n.n(r),a=(n(89),n(139)),o=function(){function e(){var e=this;i()(this,"store",{should_obtain_cookie_consent:!1,features:{}}),i()(this,"fetch",(function(){return Object(a.b)()?e.api.Settings.fetch(e.session_id).then((function(t){e.store=t})):Promise.resolve()})),i()(this,"get",(function(){return e.store})),i()(this,"getFeatures",(function(){return e.store.features})),i()(this,"getSessionId",(function(){return e.session_id})),i()(this,"isBucketed",(function(){var t=e.getFeatures();return Object.keys(t).some((function(e){return null!==t[e].version}))}))}var t=e.prototype;return t.initialize=function(e,t){this.api=e,this.session_id={session_id:t}},t.getExperimentData=function(e){var t=this.getFeatures();return t[e]?{experiment_key:e,bucket:t[e].bucket,version:t[e].version}:void 0},e}();t.a=new o},65:function(e,t,n){"use strict";n.d(t,"a",(function(){return c}));var r=n(2),i=n.n(r),a=n(38),o=function(e){var t=e.headers,n=t&&t["content-type"];return"string"==typeof n&&n.indexOf("application/json")>=0&&e.body?JSON.parse(e.body):null},s={host:"https://cdn.syndication.twimg.com"},c=function(){function e(e){this.client=new a.a(i()({},s,e))}var t=e.prototype;return t.dispatch=function(e){return this.client.dispatch(e).then(o)},t.get=function(e,t,n){return this.dispatch({path:"/"+e,method:"GET",params:t,headers:n||{}})},e}()},75:function(e,t,n){"use strict";n(42);var r=n(43),i=n.n(r),a=/(?:^|(?:https?:)?\/\/(?:www\.)?twitter\.com(?::\d+)?\/(?:#!\/)?[\w_]+\/status(?:es)?\/)(\d+)/i,o=["twitter.com","mobile.twitter.com"];t.a={isStatusUrl:function(e){return"string"==typeof e&&a.test(e)},isTwitterDotComLink:function(e){try{var t=new URL(e).host;return o.indexOf(t)>-1}catch(e){return!1}},parseQueryString:function(e){void 0===e&&(e="");try{return i.a.parse(e.replace(/^\?/,""))}catch(e){if(e instanceof URIError)return{};throw e}}}},76:function(e,t,n){"use strict";var r=n(186),i=n(49),a=Object(r.a)({loader:function(){return Object(i.a)().then((function(){return Promise.all([n.e(46),n.e(10)]).then(n.bind(null,297))}))},renderPlaceholder:function(){return null}});t.a=a},77:function(e,t,n){"use strict";var r=n(2),i=n.n(r),a=n(0),o=n(18),s=n(45),c=n.n(s),u=n(6);n(76);t.a=function(e,t,n){var r=t.lang,s=t.theme;o.a.setLocale(r),u.a.setTheme(s);var f=document.getElementById("app")||document.getElementsByTagName("div")[0];return new Promise((function(t,r){c.a.render(a.createElement(e,i()({},n,{__self:void 0,__source:{fileName:"/data/jenkins/workspace/source_2/syndication/embed-iframe/src/client/render.js",lineNumber:26,columnNumber:21}})),f,t)}))}},8:function(e,t,n){"use strict";n.d(t,"a",(function(){return m})),n.d(t,"b",(function(){return j})),n.d(t,"c",(function(){return v})),n.d(t,"d",(function(){return E})),n.d(t,"e",(function(){return g})),n.d(t,"f",(function(){return _})),n.d(t,"h",(function(){return T})),n.d(t,"g",(function(){return l}));var r=n(18),i=n(15),a=n(2),o=n.n(a),s=n(87),c=n.n(s),u=function(e){return!0},f=function(e){return e},d=function(e,t){return e[t]},l=function(e,t){return t.reduce((function(t,n){var r,i=n.key,a=c()(n,["key"]),s=a.accessor,l=void 0===s?d:s,h=a.required,m=void 0!==h&&h,p=a.validate,j=void 0===p?u:p,v=a.transform,E=void 0===v?f:v,g=a.fallback,_=l(e,i);if(void 0!==_&&j(_)){var T,b=E(_);if(void 0!==b)return o()({},t,((T={})[i]=b,T))}if(void 0!==g)return o()({},t,((r={})[i]=g,r));if(m)throw new Error(i+" is a required parameter");return t}),{})},h=/^[a-zA-Z0-9-]+$/,m=/^\d+$/,p=function(e){return e.replace(/[^a-zA-Z0-9-_:/?=@.]/g,"")},j={key:"dnt",validate:function(e){return["true","false"].includes(e)},transform:function(e){return"true"===e},fallback:!1},v={key:"embedId",validate:function(e){return h.test(e)},fallback:"embed-0"},E={key:"lang",validate:function(e){return r.a.isSupportedLocale(e)},fallback:"en"},g={key:"pageData",accessor:function(e){return l(e,[{key:"origin",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"frame",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"partner",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"siteScreenName",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"siteUserId",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"creatorScreenName",validate:function(e){return"string"==typeof e},transform:p,fallback:""},{key:"creatorUserId",validate:function(e){return"string"==typeof e},transform:p,fallback:""}])}},_={key:"theme",validate:function(e){return[i.e.ThemePaletteNames.light,i.e.ThemePaletteNames.dark].includes(e)},fallback:i.e.ThemePaletteNames.light,transform:function(e){return e===i.e.ThemePaletteNames.dark?i.e.ThemePaletteNames.darker:e}},T={key:"widgetsVersion",accessor:function(e){return e.widgetsVersion},validate:function(e){return"string"==typeof e&&/^([a-zA-Z0-9])+:([0-9])+$/.test(e)},fallback:void 0}},89:function(e,t,n){"use strict";n.d(t,"a",(function(){return r}));var r=function(e){this.Tweet=function(e){return{fetch:function(t,n){return e.get("tweet",t,n).then((function(e){return e&&e.id_str?Promise.resolve(e):Promise.reject(new Error("could not parse api response"))}))}}}(e),this.Settings=function(e){return{fetch:function(t,n){return e.get("settings",t,n).then((function(e){return e&&e.features?Promise.resolve(e):Promise.reject(new Error("could not parse api response"))}))}}}(e)}},90:function(e,t,n){"use strict";n.d(t,"a",(function(){return r})),n.d(t,"b",(function(){return i}));var r=Object.freeze({TWEET:0}),i=function(e){var t=e.client,n=void 0===t?"":t,r=e.page,i=void 0===r?"":r,a=e.section,o=void 0===a?"":a,s=e.component,c=void 0===s?"":s,u=e.element,f=void 0===u?"":u,d=e.action;return n+":"+i+":"+o+":"+c+":"+f+":"+(void 0===d?"":d)}},92:function(e,t,n){"use strict";n.d(t,"b",(function(){return o})),n.d(t,"a",(function(){return s}));var r=n(2),i=n.n(r),a=n(42),o=Object.freeze({CLICK:"click",INITIALIZED:"initialized",LIKE:"like",NO_RESULTS:"no_results",RENDERED:"rendered",RESIZE:"resize",RESULTS:"results",TRIGGER:"trigger"}),s=Object.freeze({INTENT:"intent"}),c=function(){function e(){}var t=e.prototype;return t.initialize=function(e){var t=e.embedId,n=e.data;this._embedId=t,this._data=n||{}},t.send=function(e){var t,n=e.key,r=e.details,o=window.parent;if(o&&o.postMessage){var s="twttr.private."+n,c={jsonrpc:"2.0",method:s,id:this._embedId,params:[i()({},r,{data:this._data})]};Object(a.a)("[rpc] MESSAGE "+s,r),o.postMessage(((t={})["twttr.embed"]=c,t),"*")}},e}();t.c=new c}},[[350,2,1]]]);