# Static Files

- /static		Location of dependencies to be served with no processing, or else treated as a pure file internally. Readonly unless noted.

- - /static/css		Global stylesheets for UI runtime
- - /static/js		Global JS for UI runtime
- - /static/img		Global imgs for UI runtime
- - /static/[media]	Other globally available assets. Will exist for all domains project serves.

- - /static/theme	Contains special packaging structure to assign CSS, JS modules and other assets to typed Compositions, Components, etc.
- - /static/tool	System-oriented and project-oriented GUI tools
- - /static/report	Generated HTML reports and plotting data JSON/CSV (approach given write permissions)
- - /static/upload	User uploaded content. Often links to a network share. Has user directories and write permissions

