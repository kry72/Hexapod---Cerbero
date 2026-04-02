#include "config.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>CERBERO</title>
<style>
*{box-sizing:border-box;margin:0;padding:0;font-family:system-ui,sans-serif}
body{background:#0a0a0f;color:#e0e0e0;padding:16px;max-width:440px;margin:0 auto}
.header{display:flex;align-items:center;justify-content:space-between;padding-bottom:16px;border-bottom:0.5px solid #222;margin-bottom:16px}
.title{font-size:22px;font-weight:500;color:#fff;letter-spacing:2px}
.status{font-size:12px;color:#00ff88;margin-top:4px}
.dot{width:8px;height:8px;border-radius:50%;background:#00ff88;display:inline-block;margin-right:6px}
.header-right{display:flex;align-items:center;gap:12px}
.wifi-icon{display:flex;align-items:flex-end;gap:2px;height:16px}
.wifi-bar{width:3px;background:#0066ff;border-radius:1px}
.batt-wrap{display:flex;flex-direction:column;align-items:center;gap:2px}
.batt-body{width:22px;height:11px;border:1px solid #0066ff;border-radius:2px;padding:1px;display:flex;align-items:center}
.batt-fill{height:100%;background:#0066ff;border-radius:1px}
.batt-tip{width:2px;height:5px;background:#0066ff;border-radius:0 1px 1px 0;margin-left:1px}
.tabs{display:flex;gap:6px;margin-bottom:18px}
.tab{flex:1;padding:9px 4px;border-radius:8px;border:0.5px solid #222;background:transparent;color:#444;font-size:11px;cursor:pointer;text-align:center}
.tab.active{border-color:#0066ff;color:#0066ff;background:#0066ff12}
.section-title{font-size:10px;letter-spacing:1.5px;color:#444;text-transform:uppercase;margin-bottom:10px}
.card{background:#0d0d18;border:0.5px solid #1a1a2e;border-radius:12px;padding:14px;margin-bottom:10px}
.card-header{display:flex;align-items:center;justify-content:space-between;margin-bottom:12px}
.card-title{font-size:13px;font-weight:500;color:#e0e0e0}
.card-sub{font-size:10px;color:#444;margin-top:2px}
.toggle{width:40px;height:22px;border-radius:11px;background:#1a1a2e;border:none;cursor:pointer;position:relative;transition:background 0.2s}
.toggle.on{background:#0066ff}
.toggle::after{content:'';position:absolute;width:16px;height:16px;border-radius:50%;background:#fff;top:3px;left:3px;transition:transform 0.2s}
.toggle.on::after{transform:translateX(18px)}
.row{display:flex;align-items:center;gap:8px;margin-bottom:10px}
.row label{font-size:11px;color:#444;min-width:80px}
.row input[type=range]{flex:1;accent-color:#0066ff}
.row .val{font-size:11px;color:#0066ff;min-width:30px;text-align:right}
.colors{display:flex;gap:6px;margin-bottom:10px}
.cdot{width:24px;height:24px;border-radius:50%;cursor:pointer;border:2px solid transparent}
.cdot.sel{border-color:#fff}
.anim-grid{display:grid;grid-template-columns:1fr 1fr;gap:6px}
.abtn{padding:8px;border-radius:8px;border:0.5px solid #1a1a2e;background:transparent;color:#555;font-size:11px;cursor:pointer;text-align:center}
.abtn.active{border-color:#0066ff;color:#0066ff;background:#0066ff12}
.divider{height:0.5px;background:#1a1a2e;margin:12px 0}
.mode-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px;margin-bottom:12px}
.mode-btn{padding:14px 10px;border-radius:10px;border:0.5px solid #1a1a2e;background:#0a0a15;cursor:pointer;text-align:center}
.mode-btn.active{border-color:#0066ff;background:#0066ff12}
.mode-name{font-size:12px;font-weight:500;color:#e0e0e0;margin-top:6px}
.mode-sub{font-size:10px;color:#444;margin-top:2px}
.mode-btn.active .mode-name{color:#0066ff}
.joystick-area{display:flex;justify-content:center;margin:16px 0}
.joystick-outer{width:120px;height:120px;border-radius:50%;border:0.5px solid #1a1a2e;background:#0a0a15;display:flex;align-items:center;justify-content:center}
.joystick-inner{width:44px;height:44px;border-radius:50%;background:#0066ff;opacity:0.8}
.dir-btns{display:grid;grid-template-columns:1fr 1fr 1fr;gap:6px;margin-bottom:12px}
.dir-btn{padding:10px;border-radius:8px;border:0.5px solid #1a1a2e;background:#0a0a15;color:#666;font-size:16px;cursor:pointer;text-align:center}
.dir-btn.stop{background:#ff000015;border-color:#ff3333;color:#ff3333;font-size:12px}
.stat-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px}
.stat-card{background:#0a0a15;border-radius:8px;padding:10px;border:0.5px solid #1a1a2e}
.stat-label{font-size:10px;color:#444;margin-bottom:4px}
.stat-val{font-size:18px;font-weight:500;color:#0066ff}
.cam-placeholder{background:#0a0a15;border:0.5px solid #1a1a2e;border-radius:12px;height:180px;display:flex;flex-direction:column;align-items:center;justify-content:center;gap:8px}
.leg-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px;margin-bottom:14px}
.leg-btn{padding:10px 6px;border-radius:8px;border:0.5px solid #1a1a2e;background:#0a0a15;color:#555;font-size:12px;cursor:pointer;text-align:center}
.leg-btn.active{border-color:#0066ff;color:#0066ff;background:#0066ff12}
.cycle-row{display:flex;gap:8px;margin-bottom:14px}
.cycle-btn{flex:1;padding:10px;border-radius:8px;border:0.5px solid #1a1a2e;background:#0a0a15;color:#777;font-size:11px;cursor:pointer;text-align:center}
.c0{border-color:#ff6600!important;color:#ff6600!important;background:#ff660015!important}
.c1{border-color:#00ff88!important;color:#00ff88!important;background:#00ff8815!important}
.cn{border-color:#0066ff!important;color:#0066ff!important;background:#0066ff15!important}
.servo-row{margin-bottom:12px}
.servo-label{display:flex;justify-content:space-between;margin-bottom:6px}
.servo-name{font-size:12px;color:#888}
.servo-val{font-size:12px;color:#0066ff;font-weight:500}
.save-btn{font-size:11px;padding:3px 10px;border-radius:6px;border:0.5px solid #00ff88;background:transparent;color:#00ff88;cursor:pointer}
.info-row{display:flex;gap:8px;margin-top:12px}
.info-badge{flex:1;background:#0a0a15;border-radius:8px;padding:8px;text-align:center;border:0.5px solid #1a1a2e}
.info-badge-label{font-size:10px;color:#444;margin-bottom:2px}
.info-badge-val{font-size:13px;font-weight:500;color:#e0e0e0}
.saved-vals{background:#0a0a15;border-radius:8px;padding:12px;margin-top:12px;border:0.5px solid #1a1a2e}
.saved-title{font-size:10px;color:#444;margin-bottom:8px;letter-spacing:1px;text-transform:uppercase}
.saved-row{display:flex;justify-content:space-between;padding:4px 0;border-bottom:0.5px solid #1a1a22}
.saved-row:last-child{border-bottom:none}
.saved-key{font-size:12px;color:#555}
.saved-val{font-size:12px;color:#00ff88;font-weight:500}
.page{display:none}
.page.active{display:block}
</style>
</head>
<body>

<div class="header">
  <div>
    <div class="title">CERBERO</div>
    <div class="status"><span class="dot"></span><span id="ipaddr">connessione...</span></div>
  </div>
  <div class="header-right">
    <div style="display:flex;flex-direction:column;align-items:center;gap:2px">
      <div class="wifi-icon">
        <div class="wifi-bar" style="height:4px;opacity:0.3"></div>
        <div class="wifi-bar" style="height:7px;opacity:0.5"></div>
        <div class="wifi-bar" style="height:10px;opacity:0.8"></div>
        <div class="wifi-bar" style="height:14px" id="wifiBar4"></div>
      </div>
      <span style="font-size:9px;color:#0066ff" id="wifiLabel">WiFi</span>
    </div>
    <div class="batt-wrap">
      <div style="display:flex;align-items:center">
        <div class="batt-body"><div class="batt-fill" id="battFill" style="width:75%"></div></div>
        <div class="batt-tip"></div>
      </div>
      <span style="font-size:9px;color:#0066ff" id="battLabel">75%</span>
    </div>
  </div>
</div>

<div class="tabs">
  <div class="tab active" onclick="switchTab('luci',this)">LUCI</div>
  <div class="tab" onclick="switchTab('controllo',this)">CTRL</div>
  <div class="tab" onclick="switchTab('modalita',this)">MODE</div>
  <div class="tab" onclick="switchTab('zampe',this)">ZAMPE</div>
  <div class="tab" onclick="switchTab('cam',this)">CAM</div>
</div>

<!-- LUCI -->
<div class="page active" id="page-luci">
  <div class="section-title">Colore principale</div>
  <div class="card">
    <div class="colors" id="legsColors">
      <div class="cdot sel" style="background:#0066ff" onclick="setLegsColor(0,0,255,this)"></div>
      <div class="cdot" style="background:#ff0033" onclick="setLegsColor(255,0,51,this)"></div>
      <div class="cdot" style="background:#00ff88" onclick="setLegsColor(0,255,136,this)"></div>
      <div class="cdot" style="background:#ff6600" onclick="setLegsColor(255,102,0,this)"></div>
      <div class="cdot" style="background:#cc00ff" onclick="setLegsColor(204,0,255,this)"></div>
      <div class="cdot" style="background:#ffffff" onclick="setLegsColor(255,255,255,this)"></div>
    </div>
    <div class="row"><label>Luminosità</label><input type="range" min="0" max="100" value="70" step="1" oninput="send({cmd:'legs_brightness',val:parseInt(this.value)});this.nextElementSibling.textContent=this.value+'%'"><span class="val">70%</span></div>
    <div class="row"><label>Velocità anim</label><input type="range" min="1" max="100" value="50" step="1" oninput="send({cmd:'legs_speed',val:parseInt(this.value)});this.nextElementSibling.textContent=this.value+'%'"><span class="val">50%</span></div>
  </div>

  <div class="section-title">Animazioni zampe</div>
  <div class="card">
    <div class="anim-grid">
      <div class="abtn active" onclick="setAnim('legs_anim','rotazione',this)">Rotazione</div>
      <div class="abtn" onclick="setAnim('legs_anim','kitt',this)">K.I.T.T.</div>
      <div class="abtn" onclick="setAnim('legs_anim','wave',this)">Wave</div>
      <div class="abtn" onclick="setAnim('legs_anim','idle',this)">Idle blu</div>
    </div>
  </div>

  <div class="section-title">Ring grosso</div>
  <div class="card">
    <div class="card-header">
      <div><div class="card-title">Ring 60 LED</div><div class="card-sub">pin 6</div></div>
      <button class="toggle on" onclick="toggleCmd('ring_on',this)"></button>
    </div>
    <div class="colors" id="ringColors">
      <div class="cdot sel" style="background:#ffffff" onclick="setRingColor(255,255,255,this)"></div>
      <div class="cdot" style="background:#ff0033" onclick="setRingColor(255,0,51,this)"></div>
      <div class="cdot" style="background:#0066ff" onclick="setRingColor(0,102,255,this)"></div>
    </div>
    <div class="row"><label>Luminosità</label><input type="range" min="0" max="100" value="60" step="1" oninput="send({cmd:'ring_brightness',val:parseInt(this.value)});this.nextElementSibling.textContent=this.value+'%'"><span class="val">60%</span></div>
  </div>

  <div class="section-title">Occhio</div>
  <div class="card">
    <div class="card-header">
      <div><div class="card-title">Ring 12 + 8 + 1</div><div class="card-sub">pin 5 — 21 LED</div></div>
      <button class="toggle on" onclick="toggleCmd('eyes_on',this)"></button>
    </div>
    <div class="anim-grid">
      <div class="abtn active" onclick="setAnim('eyes_anim','respiro',this)">Respiro</div>
      <div class="abtn" onclick="setAnim('eyes_anim','pulsar',this)">Pulsar</div>
      <div class="abtn" onclick="setAnim('eyes_anim','arancione',this)">Arancione</div>
      <div class="abtn" onclick="setAnim('eyes_anim','scan',this)">Scan</div>
    </div>
    <div class="row" style="margin-top:10px"><label>Luminosità</label><input type="range" min="0" max="100" value="80" step="1" oninput="send({cmd:'eyes_brightness',val:parseInt(this.value)});this.nextElementSibling.textContent=this.value+'%'"><span class="val">80%</span></div>
  </div>
</div>

<!-- CONTROLLO -->
<div class="page" id="page-controllo">
  <div class="section-title">Joystick</div>
  <div class="card">
    <div class="joystick-area">
      <div class="joystick-outer">
        <div class="joystick-inner"></div>
      </div>
    </div>
    <div class="dir-btns">
      <div class="dir-btn" onclick="send({cmd:'move',dir:'rotL'})">↺</div>
      <div class="dir-btn" onclick="send({cmd:'move',dir:'fwd'})">↑</div>
      <div class="dir-btn" onclick="send({cmd:'move',dir:'rotR'})">↻</div>
      <div class="dir-btn" onclick="send({cmd:'move',dir:'left'})">←</div>
      <div class="dir-btn stop" onclick="send({cmd:'move',dir:'stop'})">STOP</div>
      <div class="dir-btn" onclick="send({cmd:'move',dir:'right'})">→</div>
      <div class="dir-btn"></div>
      <div class="dir-btn" onclick="send({cmd:'move',dir:'back'})">↓</div>
      <div class="dir-btn"></div>
    </div>
    <div class="row"><label>Velocità</label><input type="range" min="1" max="100" value="50" step="1" oninput="send({cmd:'speed',val:parseInt(this.value)});this.nextElementSibling.textContent=this.value+'%'"><span class="val">50%</span></div>
  </div>
</div>

<!-- MODALITA -->
<div class="page" id="page-modalita">
  <div class="section-title">Modalità operative</div>
  <div class="mode-grid">
    <div class="mode-btn active" onclick="setMode('core',this)">
      <div style="font-size:20px">◉</div>
      <div class="mode-name">Core</div>
      <div class="mode-sub">standby blu</div>
    </div>
    <div class="mode-btn" onclick="setMode('patrol',this)">
      <div style="font-size:20px">⬡</div>
      <div class="mode-name">Patrol</div>
      <div class="mode-sub">movimento auto</div>
    </div>
    <div class="mode-btn" onclick="setMode('follow',this)">
      <div style="font-size:20px">◎</div>
      <div class="mode-name">Follow</div>
      <div class="mode-sub">segue persona</div>
    </div>
    <div class="mode-btn" onclick="setMode('demo',this)">
      <div style="font-size:20px">✦</div>
      <div class="mode-name">Demo</div>
      <div class="mode-sub">show completo</div>
    </div>
    <div class="mode-btn" onclick="setMode('alert',this)">
      <div style="font-size:20px">▲</div>
      <div class="mode-name">Alert</div>
      <div class="mode-sub">rosso allarme</div>
    </div>
    <div class="mode-btn" onclick="setMode('stealth',this)">
      <div style="font-size:20px">◌</div>
      <div class="mode-name">Stealth</div>
      <div class="mode-sub">LED minimi</div>
    </div>
  </div>

  <div class="section-title">Stato sistema</div>
  <div class="card">
    <div class="stat-grid">
      <div class="stat-card"><div class="stat-label">Batteria</div><div class="stat-val" id="statBatt">75%</div></div>
      <div class="stat-card"><div class="stat-label">Uptime</div><div class="stat-val" id="statUptime">0m</div></div>
      <div class="stat-card"><div class="stat-label">Temp ESP32</div><div class="stat-val" id="statTemp">--°C</div></div>
      <div class="stat-card"><div class="stat-label">WiFi RSSI</div><div class="stat-val" id="statRssi">--dB</div></div>
    </div>
  </div>
</div>

<!-- ZAMPE -->
<div class="page" id="page-zampe">
  <div class="section-title">Seleziona zampa</div>
  <div class="card">
    <div class="leg-grid" id="legGrid">
      <div class="leg-btn active" onclick="selectLeg(1,this)">LF<br><span style="font-size:10px;color:#444">front-left</span></div>
      <div class="leg-btn" onclick="selectLeg(0,this)">RF<br><span style="font-size:10px;color:#444">front-right</span></div>
      <div class="leg-btn" onclick="selectLeg(3,this)">LM<br><span style="font-size:10px;color:#444">mid-left</span></div>
      <div class="leg-btn" onclick="selectLeg(2,this)">RM<br><span style="font-size:10px;color:#444">mid-right</span></div>
      <div class="leg-btn" onclick="selectLeg(5,this)">LB<br><span style="font-size:10px;color:#444">back-left</span></div>
      <div class="leg-btn" onclick="selectLeg(4,this)">RB<br><span style="font-size:10px;color:#444">back-right</span></div>
    </div>
    <div class="divider"></div>
    <div class="section-title">Cicli</div>
    <div class="cycle-row">
      <div class="cycle-btn c0" onclick="sendLegCmd('ciclo0')">Ciclo 0<br><span style="font-size:10px;opacity:0.7">standby</span></div>
      <div class="cycle-btn c1" onclick="sendLegCmd('ciclo1')">Ciclo 1<br><span style="font-size:10px;opacity:0.7">wake up</span></div>
      <div class="cycle-btn cn" onclick="sendLegCmd('neutro')">Neutro<br><span style="font-size:10px;opacity:0.7">90°</span></div>
    </div>
    <div class="divider"></div>
    <div class="section-title">Controllo manuale</div>
    <div class="servo-row">
      <div class="servo-label"><span class="servo-name">Coxa</span><div style="display:flex;align-items:center;gap:8px"><span class="servo-val" id="coxaVal">90°</span><button class="save-btn" onclick="saveVal('coxa')">Salva</button></div></div>
      <input type="range" style="width:100%;accent-color:#0066ff" min="0" max="180" value="90" oninput="document.getElementById('coxaVal').textContent=this.value+'°';sendServo('coxa',parseInt(this.value))">
    </div>
    <div class="servo-row">
      <div class="servo-label"><span class="servo-name">Femur</span><div style="display:flex;align-items:center;gap:8px"><span class="servo-val" id="femurVal">90°</span><button class="save-btn" onclick="saveVal('femur')">Salva</button></div></div>
      <input type="range" style="width:100%;accent-color:#0066ff" min="0" max="180" value="90" oninput="document.getElementById('femurVal').textContent=this.value+'°';sendServo('femur',parseInt(this.value))">
    </div>
    <div class="servo-row">
      <div class="servo-label"><span class="servo-name">Tibia</span><div style="display:flex;align-items:center;gap:8px"><span class="servo-val" id="tibiaVal">90°</span><button class="save-btn" onclick="saveVal('tibia')">Salva</button></div></div>
      <input type="range" style="width:100%;accent-color:#0066ff" min="0" max="180" value="90" oninput="document.getElementById('tibiaVal').textContent=this.value+'°';sendServo('tibia',parseInt(this.value))">
    </div>
    <div class="divider"></div>
    <div class="section-title" id="chTitle">Canali — LF</div>
    <div class="info-row">
      <div class="info-badge"><div class="info-badge-label">Coxa</div><div class="info-badge-val" id="chCoxa">ch 6</div></div>
      <div class="info-badge"><div class="info-badge-label">Femur</div><div class="info-badge-val" id="chFemur">ch 5</div></div>
      <div class="info-badge"><div class="info-badge-label">Tibia</div><div class="info-badge-val" id="chTibia">ch 4</div></div>
      <div class="info-badge"><div class="info-badge-label">Driver</div><div class="info-badge-val" id="chDriver">0x40</div></div>
    </div>
    <div class="saved-vals">
      <div class="saved-title" id="savedTitle">Valori salvati — LF</div>
      <div class="saved-row"><span class="saved-key">Coxa centro</span><span class="saved-val" id="sv_coxa">—</span></div>
      <div class="saved-row"><span class="saved-key">Femur centro</span><span class="saved-val" id="sv_femur">—</span></div>
      <div class="saved-row"><span class="saved-key">Tibia centro</span><span class="saved-val" id="sv_tibia">—</span></div>
    </div>
  </div>
</div>

<!-- CAM -->
<div class="page" id="page-cam">
  <div class="section-title">Camera live</div>
  <div class="cam-placeholder">
    <div style="font-size:32px;color:#1a1a2e">◉</div>
    <div style="font-size:13px;color:#444">Camera non configurata</div>
    <div style="font-size:11px;color:#333;margin-top:4px">disponibile in futuro</div>
  </div>
</div>

<script>
var ws=new WebSocket('ws://'+location.hostname+'/ws');
var currentLeg=1;
var legNames=['RF','LF','RM','LM','RB','LB'];
var legChannels=[
  {coxa:2,femur:1,tibia:0,driver:'0x40'},
  {coxa:6,femur:5,tibia:4,driver:'0x40'},
  {coxa:13,femur:14,tibia:15,driver:'0x40'},
  {coxa:2,femur:1,tibia:0,driver:'0x41'},
  {coxa:9,femur:10,tibia:11,driver:'0x41'},
  {coxa:13,femur:14,tibia:15,driver:'0x41'}
];
var savedVals=[{},{},{},{},{},{}];

ws.onopen=function(){
  document.getElementById('ipaddr').textContent='online — '+location.hostname;
  ws.send('getStatus');
  setInterval(function(){if(ws.readyState===1)ws.send('getStats');},5000);
};
ws.onmessage=function(e){
  var d=JSON.parse(e.data);
  if(d.ip) document.getElementById('ipaddr').textContent='online — '+d.ip;
  if(d.wifi) document.getElementById('wifiLabel').textContent=d.wifi;
  if(d.rssi){
    document.getElementById('statRssi').textContent=d.rssi+'dB';
    var bars=d.rssi>-60?4:d.rssi>-70?3:d.rssi>-80?2:1;
    document.getElementById('wifiBar4').style.opacity=bars>=4?'1':'0.2';
  }
  if(d.temp) document.getElementById('statTemp').textContent=Math.round(d.temp)+'°C';
  if(d.uptime){
    var m=Math.floor(d.uptime/60);
    document.getElementById('statUptime').textContent=m>60?Math.floor(m/60)+'h':m+'m';
  }
  if(d.batt){
    var pct=Math.round(d.batt);
    document.getElementById('statBatt').textContent=pct+'%';
    document.getElementById('battLabel').textContent=pct+'%';
    document.getElementById('battFill').style.width=pct+'%';
  }
};
ws.onclose=function(){
  document.getElementById('ipaddr').textContent='disconnesso';
  document.querySelector('.dot').style.background='#ff3333';
};

function send(obj){if(ws.readyState===1)ws.send(JSON.stringify(obj));}
function switchTab(page,el){
  document.querySelectorAll('.tab').forEach(t=>t.classList.remove('active'));
  document.querySelectorAll('.page').forEach(p=>p.classList.remove('active'));
  el.classList.add('active');
  document.getElementById('page-'+page).classList.add('active');
}
function toggleCmd(cmd,btn){btn.classList.toggle('on');send({cmd:cmd,val:btn.classList.contains('on')});}
function setLegsColor(r,g,b,el){
  document.querySelectorAll('#legsColors .cdot').forEach(d=>d.classList.remove('sel'));
  el.classList.add('sel');
  send({cmd:'legs_color',r:r,g:g,b:b});
}
function setRingColor(r,g,b,el){
  document.querySelectorAll('#ringColors .cdot').forEach(d=>d.classList.remove('sel'));
  el.classList.add('sel');
  send({cmd:'ring_color',r:r,g:g,b:b});
}
function setAnim(cmd,val,el){
  el.parentElement.querySelectorAll('.abtn').forEach(b=>b.classList.remove('active'));
  el.classList.add('active');
  send({cmd:cmd,val:val});
}
function setMode(mode,el){
  document.querySelectorAll('.mode-btn').forEach(b=>b.classList.remove('active'));
  el.classList.add('active');
  send({cmd:'mode',val:mode});
}
function selectLeg(idx,el){
  currentLeg=idx;
  document.querySelectorAll('.leg-btn').forEach(b=>b.classList.remove('active'));
  el.classList.add('active');
  var ch=legChannels[idx];
  var name=legNames[idx];
  document.getElementById('chTitle').textContent='Canali — '+name;
  document.getElementById('savedTitle').textContent='Valori salvati — '+name;
  document.getElementById('chCoxa').textContent='ch '+ch.coxa;
  document.getElementById('chFemur').textContent='ch '+ch.femur;
  document.getElementById('chTibia').textContent='ch '+ch.tibia;
  document.getElementById('chDriver').textContent=ch.driver;
  document.querySelectorAll('.servo-row input[type=range]').forEach(s=>s.value=90);
  document.getElementById('coxaVal').textContent='90°';
  document.getElementById('femurVal').textContent='90°';
  document.getElementById('tibiaVal').textContent='90°';
  updateSavedDisplay();
}
function sendServo(servo,val){send({cmd:'servo',leg:currentLeg,servo:servo,val:val});}
function sendLegCmd(ciclo){send({cmd:'leg_ciclo',leg:currentLeg,ciclo:ciclo});}
function saveVal(servo){
  var val=parseInt(document.getElementById(servo+'Val').textContent);
  if(!savedVals[currentLeg])savedVals[currentLeg]={};
  savedVals[currentLeg][servo]=val;
  send({cmd:'save_calib',leg:currentLeg,servo:servo,val:val});
  updateSavedDisplay();
}
function updateSavedDisplay(){
  var s=savedVals[currentLeg]||{};
  document.getElementById('sv_coxa').textContent=s.coxa?s.coxa+'°':'—';
  document.getElementById('sv_femur').textContent=s.femur?s.femur+'°':'—';
  document.getElementById('sv_tibia').textContent=s.tibia?s.tibia+'°':'—';
}
</script>
</body>
</html>
)rawliteral";

void handleWsMessage(uint8_t *data, size_t len) {
  String msg = String((char*)data).substring(0, len);

  if (msg == "getStatus") {
    String resp = "{\"ip\":\"" + WiFi.localIP().toString() + "\",\"wifi\":\"" + WiFi.SSID() + "\"}";
    ws.textAll(resp);
    return;
  }

  if (msg == "getStats") {
    float temp = temperatureRead();
    unsigned long uptime = millis()/1000;
    int rssi = WiFi.RSSI();
    String resp = "{\"temp\":" + String(temp,1) +
                  ",\"uptime\":" + String(uptime) +
                  ",\"rssi\":" + String(rssi) +
                  ",\"batt\":75}";
    ws.textAll(resp);
    return;
  }

  if (msg.indexOf("\"master\"") > 0)  masterOn  = msg.indexOf("true") > 0;
  if (msg.indexOf("\"legs_on\"") > 0) legsOn    = msg.indexOf("true") > 0;
  if (msg.indexOf("\"ring_on\"") > 0) ringBigOn = msg.indexOf("true") > 0;
  if (msg.indexOf("\"eyes_on\"") > 0) eyesOn    = msg.indexOf("true") > 0;

  if (msg.indexOf("legs_brightness") > 0) {
    int v=msg.substring(msg.lastIndexOf(":")+1).toInt();
    leg01.setBrightness(map(v,0,100,0,255));
    leg23.setBrightness(map(v,0,100,0,255));
    leg45.setBrightness(map(v,0,100,0,255));
  }
  if (msg.indexOf("ring_brightness") > 0) {
    int v=msg.substring(msg.lastIndexOf(":")+1).toInt();
    ringBig.setBrightness(map(v,0,100,0,255));
  }
  if (msg.indexOf("eyes_brightness") > 0) {
    int v=msg.substring(msg.lastIndexOf(":")+1).toInt();
    eyes.setBrightness(map(v,0,100,0,255));
  }
  if (msg.indexOf("legs_anim") > 0) {
    if (msg.indexOf("rotazione") > 0)  legsAnim="rotazione";
    else if (msg.indexOf("kitt") > 0)  legsAnim="kitt";
    else if (msg.indexOf("wave") > 0)  legsAnim="wave";
    else                               legsAnim="idle";
  }
  if (msg.indexOf("eyes_anim") > 0) {
    if (msg.indexOf("respiro") > 0)     eyesAnim="respiro";
    else if (msg.indexOf("pulsar") > 0) eyesAnim="pulsar";
    else                                eyesAnim="arancione";
  }
  if (msg.indexOf("legs_color") > 0) {
    legsR=msg.substring(msg.indexOf("\"r\":")+4).toInt();
    legsG=msg.substring(msg.indexOf("\"g\":")+4).toInt();
    legsB=msg.substring(msg.indexOf("\"b\":")+4).toInt();
  }
  if (msg.indexOf("ring_color") > 0) {
    ringR=msg.substring(msg.indexOf("\"r\":")+4).toInt();
    ringG=msg.substring(msg.indexOf("\"g\":")+4).toInt();
    ringB=msg.substring(msg.indexOf("\"b\":")+4).toInt();
  }
  if (msg.indexOf("\"servo\"") > 0) {
    int legIdx=msg.substring(msg.indexOf("\"leg\":")+6).toInt();
    int val=msg.substring(msg.lastIndexOf(":")+1).toInt();
    LegChannels& lc=legs[legIdx];
    if (msg.indexOf("\"coxa\"") > 0)  moveServo(lc.driver,lc.coxa,val);
    if (msg.indexOf("\"femur\"") > 0) moveServo(lc.driver,lc.femur,val);
    if (msg.indexOf("\"tibia\"") > 0) moveServo(lc.driver,lc.tibia,val);
  }
  if (msg.indexOf("leg_ciclo") > 0) {
    int legIdx=msg.substring(msg.indexOf("\"leg\":")+6).toInt();
    LegCalib& c=calibs[legIdx];
    if (msg.indexOf("neutro") > 0) {
      moveLeg(legIdx,90,90,90);
    } else if (msg.indexOf("ciclo0") > 0) {
      moveLeg(legIdx,90,c.ciclo0Femur,c.ciclo0Tibia);
    } else if (msg.indexOf("ciclo1") > 0) {
      moveLeg(legIdx,90,c.ciclo1FemurC,c.ciclo0Tibia);
      delay(800);
      moveLeg(legIdx,90,c.ciclo1FemurA,c.ciclo0Tibia);
    }
  }
  if (msg.indexOf("save_calib") > 0) {
    int legIdx=msg.substring(msg.indexOf("\"leg\":")+6).toInt();
    int val=msg.substring(msg.lastIndexOf(":")+1).toInt();
    if (msg.indexOf("\"coxa\"") > 0)  calibs[legIdx].coxaCentro=val;
    if (msg.indexOf("\"femur\"") > 0) calibs[legIdx].femurCentro=val;
    if (msg.indexOf("\"tibia\"") > 0) calibs[legIdx].tibiaCentro=val;
  }
}

void onWsEvent(AsyncWebSocket *s, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index==0 && info->len==len && info->opcode==WS_TEXT)
      handleWsMessage(data, len);
  }
}

void setupWiFi() {
  WiFiMulti wifiMulti;
  wifiMulti.addAP("NOME_WIFI_CASA", "PASSWORD_CASA");
  wifiMulti.addAP("HOTSPOT_TELEFONO", "PASSWORD_HOTSPOT");

  Serial.print("Connessione WiFi");
  int t = 0;
  while (wifiMulti.run() != WL_CONNECTED && t < 20) {
    delay(500); Serial.print("."); t++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnesso! IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nAP: " + String(AP_SSID));
    WiFi.softAP(AP_SSID, AP_PASS);
    Serial.println("IP: " + WiFi.softAPIP().toString());
  }
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){
    r->send_P(200, "text/html", INDEX_HTML);
  });
  server.begin();
  Serial.println("Server avviato!");
}
