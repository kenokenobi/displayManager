{
  "targets": [
    {
      "target_name": "DisplayManager",
      "sources": [ "DisplayManager.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
