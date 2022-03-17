'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname + '/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');
const { exit } = require('process');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/', function (req, res) {
  res.sendFile(path.join(__dirname + '/public/index.html'));
});

// Send Style, do not change
app.get('/style.css', function (req, res) {
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname + '/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js', function (req, res) {
  fs.readFile(path.join(__dirname + '/public/index.js'), 'utf8', function (err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, { compact: true, controlFlowFlattening: true });
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function (req, res) {
  if (!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function (err) {
    if (err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function (req, res) {
  fs.stat('uploads/' + req.params.name, function (err, stat) {
    if (err == null) {
      res.sendFile(path.join(__dirname + '/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: ' + err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 

let sharedLib = ffi.Library('parser/bin/libsvgparser.so', {
 
  'isValidSVGFromFile': ['bool', ['string', 'string']],
  'getFileSize': ['int', ['string']],
  'getNumsFromFile' : ['string', ['string', 'string']],

  'getSVGDescription': ['string', ['string', 'string']],

  'getRectsImmediateChildrenSummary': ['string', ['string', 'string']],
  'getCirclesImmediateChildrenSummary': ['string', ['string', 'string']],
  'getPathsImmediateChildrenSummary': ['string', ['string', 'string']],
  'getGroupsImmediateChildrenSummary': ['string', ['string', 'string']],

  'updateSVGNameDesc': ['bool', ['string', 'string', 'string', 'string'] ]

});



//Sample endpoint
app.get('/endpoint1', function (req, res) {
  let retStr = req.query.data1 + " " + req.query.data2;

  res.send(
    {
      somethingElse: retStr
    }
  );
});



app.get('/endpoint2', function (req, res) {
  //let retStr = req.query.data1 + " " + req.query.data2;

  let retStr = "";
  let numEntries = 0;

  let titles = [];
  let fileSizes = [];

  let numRects = [];
  let numCircles = [];
  let numPaths = [];
  let numGroups = [];

  let descriptors = []; 

  let rectsComponentSummary = [];
  let circlesComponentSummary = []; 
  let pathsComponentSummary = [];
  let groupsComponentSummary = [];

  let sucessValue = true;



  const fs2 = require("node:fs/promises");

  fs.readdir("./uploads", { withFileTypes: true }, (err, files) => {
      //console.log("./uploads");
      if (err) {
        console.log(err);
      }

      else {
        files.forEach(file => {

          let svgFileName = 'uploads/' + file.name;
          let thing = sharedLib.isValidSVGFromFile(svgFileName, 'parser/bin/svg.xsd');

          if (thing == false) {
            sucessValue = false;
            console.log(file.name + ' is invalid\n');
          }

          else {

            retStr += file.name + "\n";

            titles[numEntries] = file.name;
            fileSizes[numEntries] = sharedLib.getFileSize(svgFileName);
            
            let text = sharedLib.getNumsFromFile(svgFileName, 'parser/bin/svg.xsd');
            const nums = JSON.parse(text);

            numRects[numEntries] = nums.numRect;
            numCircles[numEntries] = nums.numCirc;
            numPaths[numEntries] = nums.numPaths;
            numGroups[numEntries] = nums.numGroups;

            descriptors[numEntries] = sharedLib.getSVGDescription(svgFileName, 'parser/bin/svg.xsd');
      
            rectsComponentSummary[numEntries] = sharedLib.getRectsImmediateChildrenSummary(svgFileName, 'parser/bin/svg.xsd');
            circlesComponentSummary[numEntries] = sharedLib.getCirclesImmediateChildrenSummary(svgFileName, 'parser/bin/svg.xsd');
            pathsComponentSummary[numEntries] = sharedLib.getPathsImmediateChildrenSummary(svgFileName, 'parser/bin/svg.xsd');
            groupsComponentSummary[numEntries] = sharedLib.getGroupsImmediateChildrenSummary(svgFileName, 'parser/bin/svg.xsd');


            numEntries++;
          }
        })
      }

      res.send(
        {

          uploadStatus: sucessValue,
          names: retStr,
          entries: numEntries,
          sizes: fileSizes,
          title: titles,

          numRectangle: numRects,
          numCircle: numCircles,
          numPath : numPaths,
          numGroup : numGroups,
          
          desc: descriptors,

          rectsComponentSum : rectsComponentSummary,
          circlesComponentSum : circlesComponentSummary,
          pathsComponentSum : pathsComponentSummary,  
          groupsComponentSum : groupsComponentSummary


        }
      );
    })
});


app.get('/updateNameDescEndpoint', function (req, res) {

  let myNewName = req.query.newName;
  let myNewDesc = req.query.newDesc;


  let svgFileName = 'uploads/' + req.query.fileName

  if (sharedLib.updateSVGNameDesc(svgFileName, 'parser/bin/svg.xsd', myNewName, myNewDesc) == false){
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {
      
    }
  );
});




app.listen(portNum);
console.log('Running app at localhost: ' + portNum);