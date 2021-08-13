/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "history/view/media/history_view_file.h"

class Image;

namespace Data {
class DocumentMedia;
class WallPaper;
} // namespace Data

namespace HistoryView {

class ThemeDocument final : public File {
public:
	ThemeDocument(not_null<Element*> parent, DocumentData *document);
	ThemeDocument(
		not_null<Element*> parent,
		DocumentData *document,
		const std::optional<Data::WallPaper> &params);
	~ThemeDocument();

	void draw(
		Painter &p,
		const QRect &clip,
		TextSelection selection,
		crl::time ms) const override;
	TextState textState(QPoint point, StateRequest request) const override;

	DocumentData *getDocument() const override {
		return _data;
	}

	bool needsBubble() const override {
		return false;
	}
	bool customInfoLayout() const override {
		return false;
	}
	bool skipBubbleTail() const override {
		return true;
	}
	bool isReadyForOpen() const override;
	QString additionalInfoString() const override;

	bool hasHeavyPart() const override;
	void unloadHeavyPart() override;

	[[nodiscard]] static std::optional<Data::WallPaper> ParamsFromUrl(
		const QString &url);

protected:
	float64 dataProgress() const override;
	bool dataFinished() const override;
	bool dataLoaded() const override;

private:
	QSize countOptimalSize() override;
	QSize countCurrentSize(int newWidth) override;

	void fillPatternFieldsFrom(const QString &url);
	[[nodiscard]] bool checkGoodThumbnail() const;
	void validateThumbnail() const;
	void prepareThumbnailFrom(not_null<Image*> image, int good) const;
	void generateThumbnail() const;
	void ensureDataMediaCreated() const;

	DocumentData *_data = nullptr;
	int _pixw = 1;
	int _pixh = 1;
	mutable QPixmap _thumbnail;
	mutable int _thumbnailGood = -1; // -1 inline, 0 thumbnail, 1 good
	mutable std::shared_ptr<Data::DocumentMedia> _dataMedia;

	// For wallpaper documents.
	std::vector<QColor> _background;
	float64 _patternOpacity = 0.;
	int _gradientRotation = 0;

};

} // namespace HistoryView
